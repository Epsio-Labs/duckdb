#include "duckdb/parser/statement/compact_statement.hpp"

namespace duckdb {

CompactStatement::CompactStatement(QualifiedName table_p, bool final_sweep_p)
    : SQLStatement(StatementType::COMPACT_STATEMENT), table(std::move(table_p)), final_sweep(final_sweep_p) {
}

unique_ptr<SQLStatement> CompactStatement::Copy() const {
	return unique_ptr<CompactStatement>(new CompactStatement(*this));
}

string CompactStatement::ToString() const {
	string result = "COMPACT " + table.ToString();
	if (final_sweep) {
		result += " FINAL";
	}
	return result;
}

} // namespace duckdb
