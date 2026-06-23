#include "duckdb/optimizer/remove_derived_groups.hpp"

#include "duckdb/optimizer/optimizer.hpp"
#include "duckdb/planner/column_binding_map.hpp"
#include "duckdb/planner/expression/bound_columnref_expression.hpp"
#include "duckdb/planner/expression_iterator.hpp"
#include "duckdb/planner/operator/logical_aggregate.hpp"
#include "duckdb/planner/operator/logical_projection.hpp"

namespace duckdb {

RemoveDerivedGroups::RemoveDerivedGroups(Optimizer &optimizer) : optimizer(optimizer) {
}

unique_ptr<LogicalOperator> RemoveDerivedGroups::Optimize(unique_ptr<LogicalOperator> op) {
	op = RewritePlan(std::move(op));

	// Now that the tree is fully rewritten, redirect the operators above each inserted projection. Each remap touches
	// only its own aggregate's bindings (distinct table indices), so the order between remaps does not matter.
	for (auto &remap : pending_remaps) {
		ColumnBindingReplacer replacer;
		replacer.replacement_bindings = std::move(remap.bindings);
		replacer.stop_operator = remap.stop;
		replacer.VisitOperator(*op);
	}
	return op;
}

unique_ptr<LogicalOperator> RemoveDerivedGroups::RewritePlan(unique_ptr<LogicalOperator> op) {
	// Rewrite bottom-up: an inner aggregate's outputs become plain column references that an outer aggregate can then
	// treat as determinants.
	for (auto &child : op->children) {
		child = RewritePlan(std::move(child));
	}
	if (op->type == LogicalOperatorType::LOGICAL_AGGREGATE_AND_GROUP_BY) {
		return RewriteAggregate(std::move(op));
	}
	return op;
}

unique_ptr<LogicalOperator> RemoveDerivedGroups::RewriteAggregate(unique_ptr<LogicalOperator> op) {
	auto &aggr = op->Cast<LogicalAggregate>();

	// GROUPING() functions and multiple grouping sets (ROLLUP/CUBE/GROUPING SETS) make the identity and position of
	// groups semantically meaningful, so we leave those untouched.
	if (!aggr.grouping_functions.empty() || aggr.grouping_sets.size() > 1) {
		return op;
	}

	// This optimizer runs before statistics propagation, so group_stats should be empty. If it ever runs afterwards,
	// group_stats would need to be kept in sync with the erased groups, so bail rather than produce a wrong plan.
	if (!aggr.group_stats.empty()) {
		return op;
	}

	const idx_t group_count = aggr.groups.size();
	if (group_count < 2) {
		return op;
	}

	// Determinant columns: the bindings of group keys that are plain column references. Each of these is constant
	// within a group, so any deterministic expression over only these columns is also constant within a group.
	column_binding_set_t determinant_bindings;
	for (auto group_idx : ProjectionIndex::GetIndexes(group_count)) {
		auto &group = aggr.groups[group_idx];
		if (group->GetExpressionType() == ExpressionType::BOUND_COLUMN_REF) {
			determinant_bindings.insert(group->Cast<BoundColumnRefExpression>().binding);
		}
	}
	if (determinant_bindings.empty()) {
		return op;
	}

	// A group key is removable if it is a deterministic expression (not a plain column reference, not volatile, no
	// subquery) whose referenced columns are all determinants. A key that references no columns is a constant
	// (e.g. `GROUP BY 1, url`): it takes a single value across the whole input, so it too is constant within every
	// group and removable. At least one group always survives: determinant keys are never removed and
	// `determinant_bindings` is non-empty here, so the aggregate never collapses to a scalar aggregate (which would
	// emit one row instead of zero on empty input).
	vector<bool> removable(group_count, false);
	bool any_removable = false;
	for (auto group_idx : ProjectionIndex::GetIndexes(group_count)) {
		auto &group = aggr.groups[group_idx];
		if (group->GetExpressionType() == ExpressionType::BOUND_COLUMN_REF) {
			continue; // determinant: always kept
		}
		if (group->IsVolatile() || group->HasSubquery()) {
			continue; // value is not a pure function of its referenced columns
		}
		bool only_determinants = true;
		ExpressionIterator::VisitExpressionClass(
		    *group, ExpressionClass::BOUND_COLUMN_REF, [&](const Expression &child) {
			    if (determinant_bindings.find(child.Cast<BoundColumnRefExpression>().binding) ==
			        determinant_bindings.end()) {
				    only_determinants = false;
			    }
		    });
		if (only_determinants) {
			removable[group_idx] = true;
			any_removable = true;
		}
	}
	if (!any_removable) {
		return op;
	}

	// Assign each retained group its new (compacted) output index, and map determinant bindings to it.
	vector<ProjectionIndex> new_index(group_count);
	column_binding_map_t<ProjectionIndex> determinant_new_index;
	{
		ProjectionIndex running(0);
		for (auto group_idx : ProjectionIndex::GetIndexes(group_count)) {
			if (removable[group_idx]) {
				continue;
			}
			new_index[group_idx] = running;
			auto &group = aggr.groups[group_idx];
			if (group->GetExpressionType() == ExpressionType::BOUND_COLUMN_REF) {
				determinant_new_index[group->Cast<BoundColumnRefExpression>().binding] = running;
			}
			++running;
		}
	}

	const auto group_index = aggr.group_index;
	const auto aggregate_index = aggr.aggregate_index;
	const auto proj_index = optimizer.binder.GenerateTableIndex();

	// Build the projection that reproduces the aggregate's original output, in the same order, so that downstream
	// references can be redirected position-for-position.
	vector<unique_ptr<Expression>> proj_expressions;
	vector<ReplacementBinding> replacements;
	ProjectionIndex out_pos(0);
	auto emit = [&](ColumnBinding old_binding, unique_ptr<Expression> expr) {
		replacements.emplace_back(old_binding, ColumnBinding(proj_index, out_pos));
		proj_expressions.push_back(std::move(expr));
		++out_pos;
	};

	for (auto group_idx : ProjectionIndex::GetIndexes(group_count)) {
		auto &group = aggr.groups[group_idx];
		unique_ptr<Expression> expr;
		if (removable[group_idx]) {
			// Recompute the derived expression from the retained group outputs: every column it references is a
			// determinant, now exposed by the aggregate at (group_index, new_index).
			expr = std::move(group); // leaves a null in aggr.groups, erased below
			ExpressionIterator::VisitExpressionClassMutable(
			    expr, ExpressionClass::BOUND_COLUMN_REF, [&](unique_ptr<Expression> &child) {
				    auto &colref = child->Cast<BoundColumnRefExpression>();
				    colref.binding = ColumnBinding(group_index, determinant_new_index.at(colref.binding));
			    });
		} else {
			expr = make_uniq<BoundColumnRefExpression>(group->return_type,
			                                           ColumnBinding(group_index, new_index[group_idx]));
		}
		emit(ColumnBinding(group_index, group_idx), std::move(expr));
	}
	for (auto aggr_idx : ProjectionIndex::GetIndexes(aggr.expressions.size())) {
		emit(ColumnBinding(aggregate_index, aggr_idx),
		     make_uniq<BoundColumnRefExpression>(aggr.expressions[aggr_idx]->return_type,
		                                         ColumnBinding(aggregate_index, aggr_idx)));
	}

	// Physically remove the derived groups from the aggregate (back to front to keep indices valid).
	for (idx_t i = group_count; i-- > 0;) {
		if (removable[i]) {
			aggr.groups.erase_at(i);
		}
	}
	// Reindex the (single) grouping set against the compacted groups, dropping removed entries.
	for (auto &grouping_set : aggr.grouping_sets) {
		GroupingSet new_set;
		for (const auto old_idx : grouping_set) {
			if (!removable[old_idx]) {
				new_set.insert(new_index[old_idx]);
			}
		}
		grouping_set = std::move(new_set);
	}

	auto projection = make_uniq<LogicalProjection>(proj_index, std::move(proj_expressions));
	projection->children.push_back(std::move(op));
	projection->ResolveOperatorTypes();

	pending_remaps.push_back(PendingRemap {std::move(replacements), projection.get()});
	return std::move(projection);
}

} // namespace duckdb
