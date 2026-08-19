//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/operator/logical_pivot_materialize.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/planner/logical_operator.hpp"

namespace duckdb {

//! The result of the late-materialization rewrite: fetch child 0's columns (a
//! full-width LogicalGet describing the deferred read) for the rows that
//! survive child 1 (the original narrow pipeline). The operator's output is
//! exactly child 0's, so the projection the rewrite leaves above it keeps
//! referencing the wide get's bindings unchanged. The engine consuming the
//! plan runs the fetch, identifying the surviving rows by its own scan
//! metadata; DuckDB itself never executes this operator, so it has no
//! physical counterpart and no row-id plumbing.
class LogicalPivotMaterialize : public LogicalOperator {
public:
	static constexpr const LogicalOperatorType TYPE = LogicalOperatorType::LOGICAL_PIVOT_MATERIALIZE;

public:
	LogicalPivotMaterialize(unique_ptr<LogicalOperator> wide_get, unique_ptr<LogicalOperator> narrow)
	    : LogicalOperator(LogicalOperatorType::LOGICAL_PIVOT_MATERIALIZE) {
		children.push_back(std::move(wide_get));
		children.push_back(std::move(narrow));
	}

	vector<ColumnBinding> GetColumnBindings() override {
		return children[0]->GetColumnBindings();
	}

protected:
	void ResolveTypes() override {
		types = children[0]->types;
	}
};

} // namespace duckdb
