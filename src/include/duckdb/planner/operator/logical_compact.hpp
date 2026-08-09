//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/operator/logical_compact.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/qualified_name.hpp"
#include "duckdb/planner/logical_operator.hpp"

namespace duckdb {

//! COMPACT <table> [FINAL]: merge a table's small files into target-sized ones.
//! The engine consuming the plan runs the compaction; DuckDB itself only binds
//! the statement, so this operator has no physical counterpart.
class LogicalCompact : public LogicalOperator {
public:
	static constexpr const LogicalOperatorType TYPE = LogicalOperatorType::LOGICAL_COMPACT;

public:
	LogicalCompact(QualifiedName table_p, bool final_sweep_p)
	    : LogicalOperator(LogicalOperatorType::LOGICAL_COMPACT), table(std::move(table_p)),
	      final_sweep(final_sweep_p) {
	}

	//! The table to compact; absent catalog/schema parts are empty strings.
	QualifiedName table;
	//! FINAL: keep sweeping until a pass merges nothing.
	bool final_sweep;

public:
	idx_t EstimateCardinality(ClientContext &context) override {
		return 1;
	}

protected:
	void ResolveTypes() override {
		types.emplace_back(LogicalType::BOOLEAN);
	}
};

} // namespace duckdb
