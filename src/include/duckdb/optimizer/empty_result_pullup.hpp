//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/optimizer/deliminator.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/optimizer/column_binding_replacer.hpp"

namespace duckdb {

class Optimizer;

//! The EmptyResultPullup Optimizer traverses the logical operator tree and Pulls up empty operators when possible
class EmptyResultPullup : LogicalOperatorVisitor {
public:
	explicit EmptyResultPullup(Optimizer &optimizer) : optimizer(optimizer) {
	}

	unique_ptr<LogicalOperator> Optimize(unique_ptr<LogicalOperator> op);

private:
	Optimizer &optimizer;

	unique_ptr<LogicalOperator> PullUpEmptyJoinChildren(unique_ptr<LogicalOperator> op);
	unique_ptr<LogicalOperator> CreateNullRhs(unique_ptr<LogicalOperator> &rhs_op);
};

} // namespace duckdb
