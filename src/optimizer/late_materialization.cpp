#include "duckdb/optimizer/late_materialization.hpp"

#include "duckdb/optimizer/late_materialization_helper.hpp"
#include "duckdb/planner/operator/logical_pivot_materialize.hpp"
#include "duckdb/planner/operator/logical_filter.hpp"
#include "duckdb/planner/operator/logical_get.hpp"
#include "duckdb/planner/operator/logical_limit.hpp"
#include "duckdb/planner/operator/logical_order.hpp"
#include "duckdb/planner/operator/logical_projection.hpp"
#include "duckdb/planner/operator/logical_sample.hpp"
#include "duckdb/planner/operator/logical_top_n.hpp"
#include "duckdb/planner/expression/bound_columnref_expression.hpp"
#include "duckdb/planner/binder.hpp"
#include "duckdb/optimizer/optimizer.hpp"
#include "duckdb/planner/expression_iterator.hpp"
#include "duckdb/catalog/catalog_entry/table_catalog_entry.hpp"
#include "duckdb/main/client_config.hpp"
#include "duckdb/main/config.hpp"
#include "duckdb/main/settings.hpp"

namespace duckdb {

LateMaterialization::LateMaterialization(Optimizer &optimizer) : optimizer(optimizer) {
	max_row_count = Settings::Get<LateMaterializationMaxRowsSetting>(optimizer.context);
}

void LateMaterialization::ReplaceTopLevelTableIndex(LogicalOperator &root, TableIndex new_index) {
	reference<LogicalOperator> current_op = root;
	while (true) {
		auto &op = current_op.get();
		switch (op.type) {
		case LogicalOperatorType::LOGICAL_PROJECTION: {
			// reached a projection - modify the table index and return
			auto &proj = op.Cast<LogicalProjection>();
			proj.table_index = new_index;
			return;
		}
		case LogicalOperatorType::LOGICAL_GET: {
			// reached the root get - modify the table index and return
			auto &get = op.Cast<LogicalGet>();
			get.table_index = new_index;
			return;
		}
		case LogicalOperatorType::LOGICAL_TOP_N: {
			// visit the expressions of the operator and continue into the child node
			auto &top_n = op.Cast<LogicalTopN>();
			for (auto &order : top_n.orders) {
				ReplaceTableReferences(order.expression, new_index);
			}
			current_op = *op.children[0];
			break;
		}
		case LogicalOperatorType::LOGICAL_FILTER:
		case LogicalOperatorType::LOGICAL_SAMPLE:
		case LogicalOperatorType::LOGICAL_LIMIT: {
			// visit the expressions of the operator and continue into the child node
			for (auto &expr : op.expressions) {
				ReplaceTableReferences(expr, new_index);
			}
			current_op = *op.children[0];
			break;
		}
		default:
			throw InternalException("Unsupported operator type in LateMaterialization::ReplaceTopLevelTableIndex");
		}
	}
}

void LateMaterialization::ReplaceTableReferences(unique_ptr<Expression> &root_expr, TableIndex new_table_index) {
	ExpressionIterator::VisitExpressionMutable<BoundColumnRefExpression>(
	    root_expr, [&](BoundColumnRefExpression &bound_column_ref, unique_ptr<Expression> &expr) {
		    bound_column_ref.binding.table_index = new_table_index;
	    });
}

unique_ptr<Expression> LateMaterialization::GetExpression(LogicalOperator &op, ProjectionIndex column_index) {
	switch (op.type) {
	case LogicalOperatorType::LOGICAL_GET: {
		auto &get = op.Cast<LogicalGet>();
		ColumnBinding column_binding(get.table_index, column_index);
		auto &column_id = get.GetColumnIndex(column_binding);
		auto column_name = get.GetColumnName(column_id);
		auto &column_type = get.GetColumnType(column_id);
		auto expr = make_uniq<BoundColumnRefExpression>(column_name, column_type, column_binding);
		return std::move(expr);
	}
	case LogicalOperatorType::LOGICAL_PROJECTION: {
		auto &proj = op.Cast<LogicalProjection>();
		ColumnBinding column_binding(proj.table_index, column_index);
		auto &expr = proj.GetExpression(column_binding);
		return expr.Copy();
	}
	default:
		throw InternalException("Unsupported operator type for LateMaterialization::GetExpression");
	}
}

void LateMaterialization::ReplaceExpressionReferences(LogicalOperator &next_op, unique_ptr<Expression> &root_expr) {
	ExpressionIterator::VisitExpressionMutable<BoundColumnRefExpression>(
	    root_expr, [&](BoundColumnRefExpression &bound_column_ref, unique_ptr<Expression> &expr) {
		    expr = GetExpression(next_op, bound_column_ref.binding.column_index);
	    });
}

bool LateMaterialization::TryLateMaterialization(unique_ptr<LogicalOperator> &op) {
	// check if we can benefit from late materialization
	// we need to see how many columns we require in the pipeline versus how many columns we emit in the scan
	// for example, in a query like SELECT * FROM tbl ORDER BY ts LIMIT 5, the top-n only needs the "ts" column
	// the other columns can be fetched later on using late materialization
	// we can only push late materialization through a subset of operators
	// and we can only do it for scans that support the row-id pushdown (currently only DuckDB table scans)

	// visit the expressions for each operator in the chain
	vector<reference<LogicalOperator>> source_operators;

	VisitOperatorExpressions(*op);
	reference<LogicalOperator> child = *op->children[0];
	while (child.get().type != LogicalOperatorType::LOGICAL_GET) {
		switch (child.get().type) {
		case LogicalOperatorType::LOGICAL_PROJECTION: {
			// recurse into the child node - but ONLY visit expressions that are referenced
			auto &proj = child.get().Cast<LogicalProjection>();
			source_operators.push_back(child);

			for (auto &expr : proj.expressions) {
				if (expr->IsVolatile()) {
					// we cannot do this optimization if any of the columns are volatile
					return false;
				}
			}

			// figure out which projection expressions we are currently referencing
			set<idx_t> referenced_columns;
			for (auto &entry : column_references) {
				auto &column_binding = entry.first;
				if (column_binding.table_index == proj.table_index) {
					referenced_columns.insert(column_binding.column_index);
				}
			}
			// clear the list of referenced expressions and visit those columns
			column_references.clear();
			for (auto &col_idx : referenced_columns) {
				VisitExpression(&proj.expressions[col_idx]);
			}
			// continue into child
			child = *child.get().children[0];
			break;
		}
		case LogicalOperatorType::LOGICAL_FILTER: {
			// visit filter expressions - we need these columns
			VisitOperatorExpressions(child.get());
			// continue into child
			child = *child.get().children[0];
			break;
		}
		default:
			// unsupported operator for late materialization
			return false;
		}
	}
	auto &get = child.get().Cast<LogicalGet>();
	// [pivot] Columns referenced only by pushed-down table filters are still read
	// by the scan, so deferring them via late materialization just re-reads data
	// the scan already has. Count them as referenced so the benefit check below
	// doesn't defer them (otherwise e.g. `WHERE s <> '' ORDER BY t LIMIT n` reads
	// `s` for the filter and then fetches it again for the surviving rows).
	for (auto &entry : get.table_filters) {
		column_references[ColumnBinding(get.table_index, entry.GetIndex())];
	}
	if (column_references.size() >= get.GetColumnIds().size()) {
		// we do not benefit from late materialization
		// we need all of the columns to compute the root node anyway (Top-N/Limit/etc)
		return false;
	}
	if (!get.function.late_materialization) {
		// this function does not support late materialization
		return false;
	}
	// [pivot] A scan whose remaining columns are all virtual (e.g. only the
	// empty placeholder the pruner leaves once COUNT(*) above referenced
	// nothing) defers no real column: there is nothing to fetch, so the
	// rewrite has no benefit. Decline before altering the plan.
	bool has_physical_column = false;
	for (auto &col_id : get.GetColumnIds()) {
		if (!col_id.IsVirtualColumn()) {
			has_physical_column = true;
			break;
		}
	}
	if (!has_physical_column) {
		return false;
	}

	// we benefit from late materialization
	// [pivot] The rewrite targets pivot's executor, which identifies the
	// surviving rows by its own scan metadata rather than by row ids. Emit an
	// explicit LogicalPivotMaterialize over a wide get and the original
	// (narrow) pipeline instead of a row-id semi join: no row-id column is
	// synthesized or pushed through the plan, and no re-order by row id is
	// needed (pivot's LIMIT does not preserve scan order).

	// construct the wide get the materialize fetches from
	auto lhs = LateMaterializationHelper::CreateLHSGet(get, optimizer.binder);
	auto &lhs_get = *lhs;
	auto lhs_columns = lhs_get.GetColumnIds().size();

	// construct the final projections/orders before altering the original plan
	vector<unique_ptr<Expression>> final_proj_list;
	// construct the final projection list from either (1) the root projection, or (2) the logical get
	if (!source_operators.empty()) {
		// construct the columns from the root projection
		auto &root_proj = source_operators[0].get();
		for (auto &expr : root_proj.expressions) {
			final_proj_list.push_back(expr->Copy());
		}
		// now we need to "flatten" the projection list by traversing the set of projections and inlining them
		for (idx_t i = 0; i < source_operators.size(); i++) {
			auto &next_operator = i + 1 < source_operators.size() ? source_operators[i + 1].get() : lhs_get;
			for (auto &expr : final_proj_list) {
				ReplaceExpressionReferences(next_operator, expr);
			}
		}
	} else {
		// if we have no projection directly construct the columns from the root get
		for (idx_t i = 0; i < lhs_columns; i++) {
			final_proj_list.push_back(GetExpression(lhs_get, ProjectionIndex(i)));
		}
	}

	// [pivot] A fully pruned pipeline (e.g. COUNT(*) above, which left the
	// projection a bare constant) defers no column at all: there is nothing to
	// fetch, so the rewrite has no benefit. Decline before altering the plan.
	bool references_columns = false;
	for (auto &expr : final_proj_list) {
		ExpressionIterator::VisitExpressionMutable<BoundColumnRefExpression>(
		    expr, [&](BoundColumnRefExpression &, unique_ptr<Expression> &) { references_columns = true; });
	}
	if (!references_columns) {
		return false;
	}

	// for top-n we need to re-order by the top-n conditions at the end
	vector<BoundOrderByNode> final_orders;
	auto root_type = op->type;
	if (root_type == LogicalOperatorType::LOGICAL_TOP_N) {
		auto &top_n = op->Cast<LogicalTopN>();
		for (auto &order : top_n.orders) {
			auto expr = order.expression->Copy();
			final_orders.emplace_back(order.type, order.null_order, std::move(expr));
		}
	}

	// the final table index emitted must be the table index of the original operator
	// this ensures any upstream operators that refer to the original get will keep on referring to the correct columns
	auto final_index = source_operators.empty()
	                       ? get.table_index
	                       : source_operators[0].get().Cast<LogicalProjection>().table_index;
	// the narrow pipeline keeps running, under a fresh table index
	ReplaceTopLevelTableIndex(*op, optimizer.binder.GenerateTableIndex());

	// wrap the wide get and the narrow pipeline in the materialize
	auto materialize = make_uniq<LogicalPivotMaterialize>(std::move(lhs), std::move(op));

	// push the final projection above; for top-n the re-order goes above that
	auto proj = make_uniq<LogicalProjection>(final_index, std::move(final_proj_list));
	proj->children.push_back(std::move(materialize));
	if (root_type == LogicalOperatorType::LOGICAL_TOP_N) {
		for (auto &order : final_orders) {
			ReplaceTableReferences(order.expression, final_index);
		}
		auto order = make_uniq<LogicalOrder>(std::move(final_orders));
		order->children.push_back(std::move(proj));
		op = std::move(order);
	} else {
		op = std::move(proj);
	}

	// run the RemoveUnusedColumns optimizer to prune the (now) unused columns the plan
	RemoveUnusedColumns unused_optimizer(optimizer);
	unused_optimizer.VisitOperator(op);
	return true;
}

bool LateMaterialization::OptimizeLargeLimit(LogicalLimit &limit, idx_t limit_val, bool has_offset) {
	if (!has_offset && !Settings::Get<PreserveInsertionOrderSetting>(optimizer.context)) {
		// we avoid optimizing large limits if preserve insertion order is false
		// since the limit is executed in parallel anyway
		return false;
	}
	// we only perform this optimization until a certain amount of maximum values to reduce memory constraints
	// since we still materialize the set of row-ids in the hash table this optimization can increase memory pressure
	// FIXME: make this configurable as well
	static constexpr const idx_t LIMIT_MAX_VAL = 1000000;
	if (limit_val > LIMIT_MAX_VAL) {
		return false;
	}
	// we only support large limits if they are directly below the source
	reference<LogicalOperator> current_op = *limit.children[0];
	while (current_op.get().type != LogicalOperatorType::LOGICAL_GET) {
		if (current_op.get().type != LogicalOperatorType::LOGICAL_PROJECTION) {
			return false;
		}
		current_op = *current_op.get().children[0];
	}
	// if there are any filters we shouldn't do large limit optimization
	auto &get = current_op.get().Cast<LogicalGet>();
	if (get.table_filters.HasFilters()) {
		return false;
	}
	return true;
}

unique_ptr<LogicalOperator> LateMaterialization::Optimize(unique_ptr<LogicalOperator> op) {
	switch (op->type) {
	case LogicalOperatorType::LOGICAL_LIMIT: {
		auto &limit = op->Cast<LogicalLimit>();
		if (limit.limit_val.Type() != LimitNodeType::CONSTANT_VALUE) {
			break;
		}
		auto limit_val = limit.limit_val.GetConstantValue();
		bool has_offset = limit.offset_val.Type() != LimitNodeType::UNSET;
		if (limit_val > max_row_count) {
			// for large limits - we may still want to do this optimization if the limit is consecutive
			// this is the case if there are only projections/get below the limit
			// if the row-ids are not consecutive doing the join can worsen performance
			if (!OptimizeLargeLimit(limit, limit_val, has_offset)) {
				break;
			}
		} else {
			// optimizing small limits really only makes sense if we have an offset
			if (!has_offset) {
				break;
			}
		}
		if (TryLateMaterialization(op)) {
			return op;
		}
		break;
	}
	case LogicalOperatorType::LOGICAL_TOP_N: {
		auto &top_n = op->Cast<LogicalTopN>();
		if (top_n.limit > max_row_count) {
			break;
		}
		// for the top-n we need to visit the order elements
		if (TryLateMaterialization(op)) {
			return op;
		}
		break;
	}
	case LogicalOperatorType::LOGICAL_SAMPLE: {
		auto &sample = op->Cast<LogicalSample>();
		if (sample.sample_options->is_percentage) {
			break;
		}
		if (sample.sample_options->sample_size.GetValue<uint64_t>() > max_row_count) {
			break;
		}
		if (TryLateMaterialization(op)) {
			return op;
		}
		break;
	}
	default:
		break;
	}
	for (auto &child : op->children) {
		child = Optimize(std::move(child));
	}
	return op;
}

} // namespace duckdb
