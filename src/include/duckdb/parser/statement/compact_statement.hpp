//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/statement/compact_statement.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/qualified_name.hpp"
#include "duckdb/parser/sql_statement.hpp"

namespace duckdb {

//! COMPACT <table> [FINAL]: merge a table's small files into target-sized ones.
class CompactStatement : public SQLStatement {
public:
	static constexpr const StatementType TYPE = StatementType::COMPACT_STATEMENT;

public:
	CompactStatement(QualifiedName table_p, bool final_sweep_p);

protected:
	CompactStatement(const CompactStatement &other) = default;

public:
	unique_ptr<SQLStatement> Copy() const override;
	string ToString() const override;

	//! The table to compact.
	QualifiedName table;
	//! FINAL: keep sweeping until a pass merges nothing.
	bool final_sweep;
};

} // namespace duckdb
