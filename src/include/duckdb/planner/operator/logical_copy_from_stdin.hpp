//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/operator/logical_copy_from_stdin.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/catalog/catalog_entry/table_catalog_entry.hpp"
#include "duckdb/planner/logical_operator.hpp"

namespace duckdb {

//! COPY <table> [(columns)] FROM STDIN [WITH (...)]: load rows arriving over
//! the client protocol into a table. No copy function can read them here, so
//! the statement binds to this leaf operator and the engine consuming the plan
//! runs the ingest; there is no physical counterpart (mirrors COMPACT).
class LogicalCopyFromStdin : public LogicalOperator {
public:
	static constexpr const LogicalOperatorType TYPE = LogicalOperatorType::LOGICAL_COPY_FROM_STDIN;

public:
	LogicalCopyFromStdin(TableCatalogEntry &table_p, vector<idx_t> column_indexes_p, string format_p,
	                     vector<pair<string, vector<Value>>> options_p)
	    : LogicalOperator(LogicalOperatorType::LOGICAL_COPY_FROM_STDIN), table(table_p),
	      column_indexes(std::move(column_indexes_p)), format(std::move(format_p)), options(std::move(options_p)) {
	}

	//! The bound target table (mirrors LogicalInsert).
	TableCatalogEntry &table;
	//! The explicit column list resolved to physical column positions; empty
	//! when the statement targets every table column.
	vector<idx_t> column_indexes;
	//! The FORMAT option as written, empty when the statement gave none.
	string format;
	//! The remaining WITH (...) options, bound to constant values and sorted
	//! by name; a bare flag (e.g. HEADER) carries no values.
	vector<pair<string, vector<Value>>> options;

public:
	idx_t EstimateCardinality(ClientContext &context) override {
		return 1;
	}

protected:
	void ResolveTypes() override {
		types.emplace_back(LogicalType::BIGINT);
	}
};

} // namespace duckdb
