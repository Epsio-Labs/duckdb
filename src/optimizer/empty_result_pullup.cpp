#include "duckdb/optimizer/empty_result_pullup.hpp"
#include "duckdb/common/types/value.hpp"
#include "duckdb/common/unordered_map.hpp"
#include "duckdb/optimizer/optimizer.hpp"
#include "duckdb/planner/binder.hpp"
#include "duckdb/planner/expression/bound_constant_expression.hpp"
#include "duckdb/common/enums/logical_operator_type.hpp"
#include "duckdb/planner/operator/logical_comparison_join.hpp"
#include "duckdb/planner/operator/logical_cross_product.hpp"
#include "duckdb/planner/operator/logical_dummy_scan.hpp"
#include "duckdb/planner/operator/logical_empty_result.hpp"
#include "duckdb/planner/operator/logical_any_join.hpp"
#include "duckdb/planner/operator/logical_projection.hpp"

namespace duckdb {

unique_ptr<LogicalOperator> EmptyResultPullup::CreateNullRhs(unique_ptr<LogicalOperator> &rhs_op) {
	unordered_map<TableIndex, vector<unique_ptr<Expression>>> projection_groups;
	auto column_bindings = rhs_op->GetColumnBindings();
	rhs_op->ResolveOperatorTypes();
	auto &types = rhs_op->types;

	for (idx_t index = 0; index < column_bindings.size(); index++) {
		projection_groups[column_bindings[index].table_index].emplace_back(
		    make_uniq<BoundConstantExpression>(Value(types[index])));
	}

	auto create_null_projection = [&](TableIndex table_index) {
		auto dummy_scan = make_uniq<LogicalDummyScan>(optimizer.binder.GenerateTableIndex());
		auto projection = make_uniq<LogicalProjection>(table_index, std::move(projection_groups[table_index]));
		projection->AddChild(std::move(dummy_scan));
		return projection;
	};

	auto first = projection_groups.begin();
	D_ASSERT(first != projection_groups.end());
	unique_ptr<LogicalOperator> rhs = create_null_projection(first->first);
	projection_groups.erase(first);

	for (auto &group : projection_groups) {
		rhs = LogicalCrossProduct::Create(std::move(rhs), create_null_projection(group.first));
	}
	return rhs;
}

unique_ptr<LogicalOperator> EmptyResultPullup::PullUpEmptyJoinChildren(unique_ptr<LogicalOperator> op) {
	JoinType join_type = JoinType::INVALID;
	D_ASSERT(op->type == LogicalOperatorType::LOGICAL_COMPARISON_JOIN ||
	         op->type == LogicalOperatorType::LOGICAL_ANY_JOIN || op->type == LogicalOperatorType::LOGICAL_DELIM_JOIN ||
	         op->type == LogicalOperatorType::LOGICAL_ASOF_JOIN || op->type == LogicalOperatorType::LOGICAL_EXCEPT);
	switch (op->type) {
	case LogicalOperatorType::LOGICAL_DELIM_JOIN:
	case LogicalOperatorType::LOGICAL_ASOF_JOIN:
	case LogicalOperatorType::LOGICAL_COMPARISON_JOIN:
		join_type = op->Cast<LogicalComparisonJoin>().join_type;
		break;
	case LogicalOperatorType::LOGICAL_ANY_JOIN:
		join_type = op->Cast<LogicalAnyJoin>().join_type;
		break;
	case LogicalOperatorType::LOGICAL_EXCEPT:
		join_type = JoinType::ANTI;
		break;
	case LogicalOperatorType::LOGICAL_INTERSECT:
		join_type = JoinType::SEMI;
		break;
	default:
		break;
	}

	switch (join_type) {
	case JoinType::SEMI:
	case JoinType::INNER: {
		for (auto &child : op->children) {
			if (child->type == LogicalOperatorType::LOGICAL_EMPTY_RESULT) {
				op = make_uniq<LogicalEmptyResult>(std::move(op));
				break;
			}
		}
		break;
	}
	// For ANTI joins, if the right child is empty, the whole join collapses to the left child
	case JoinType::ANTI: {
		if (op->children[1]->type == LogicalOperatorType::LOGICAL_EMPTY_RESULT &&
		    op->type != LogicalOperatorType::LOGICAL_EXCEPT) {
			op = std::move(op->children[0]);
			break;
		}
		if (op->children[0]->type == LogicalOperatorType::LOGICAL_EMPTY_RESULT) {
			op = make_uniq<LogicalEmptyResult>(std::move(op));
		}
		break;
	}
	case JoinType::MARK:
	case JoinType::SINGLE:
	case JoinType::LEFT: {
		if (op->children[0]->type == LogicalOperatorType::LOGICAL_EMPTY_RESULT) {
			op = make_uniq<LogicalEmptyResult>(std::move(op));
		} else if ((join_type == JoinType::SINGLE || join_type == JoinType::LEFT) &&
		           op->children[1]->type == LogicalOperatorType::LOGICAL_EMPTY_RESULT) {
			// A left-preserving join against a proven-empty RHS emits every left
			// row once and pads the RHS bindings with NULL values. Materialize that
			// one NULL row so the join and any DELIM_GET dependency disappear.
			if (op->children[1]->GetColumnBindings().empty()) {
				op = std::move(op->children[0]);
			} else {
				auto null_rhs = CreateNullRhs(op->children[1]);
				op = LogicalCrossProduct::Create(std::move(op->children[0]), std::move(null_rhs));
			}
		}
		break;
	}
	default:
		break;
	}
	return op;
}

unique_ptr<LogicalOperator> EmptyResultPullup::Optimize(unique_ptr<LogicalOperator> op) {
	for (idx_t i = 0; i < op->children.size(); i++) {
		op->children[i] = Optimize(std::move(op->children[i]));
	}
	switch (op->type) {
	case LogicalOperatorType::LOGICAL_PROJECTION:
	case LogicalOperatorType::LOGICAL_FILTER:
	case LogicalOperatorType::LOGICAL_DISTINCT:
	case LogicalOperatorType::LOGICAL_WINDOW:
	case LogicalOperatorType::LOGICAL_GET:
	case LogicalOperatorType::LOGICAL_INTERSECT:
	case LogicalOperatorType::LOGICAL_PIVOT:
	case LogicalOperatorType::LOGICAL_CROSS_PRODUCT: {
		for (auto &child : op->children) {
			if (child->type == LogicalOperatorType::LOGICAL_EMPTY_RESULT) {
				op = make_uniq<LogicalEmptyResult>(std::move(op));
				break;
			}
		}
		return op;
	}
	case LogicalOperatorType::LOGICAL_MATERIALIZED_CTE: {
		D_ASSERT(op->children.size() == 2);
		if (op->children[1]->type == LogicalOperatorType::LOGICAL_EMPTY_RESULT) {
			op = make_uniq<LogicalEmptyResult>(std::move(op));
			break;
		}
		return op;
	}
	case LogicalOperatorType::LOGICAL_UNION: {
		for (auto &child : op->children) {
			if (child->type != LogicalOperatorType::LOGICAL_EMPTY_RESULT) {
				return op;
			}
		}
		op = make_uniq<LogicalEmptyResult>(std::move(op));
		break;
	}
	case LogicalOperatorType::LOGICAL_EXCEPT:
	case LogicalOperatorType::LOGICAL_ANY_JOIN:
	case LogicalOperatorType::LOGICAL_DELIM_JOIN:
	case LogicalOperatorType::LOGICAL_ASOF_JOIN:
	case LogicalOperatorType::LOGICAL_COMPARISON_JOIN: {
		op = PullUpEmptyJoinChildren(std::move(op));
		break;
	}
	default:
		break;
	}
	return op;
}

} // namespace duckdb
