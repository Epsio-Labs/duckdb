#include "duckdb/parser/statement/compact_statement.hpp"
#include "duckdb/parser/transformer.hpp"

namespace duckdb {

unique_ptr<SQLStatement> Transformer::TransformCompact(duckdb_libpgquery::PGCompactStmt &stmt) {
	return make_uniq<CompactStatement>(TransformQualifiedName(*stmt.relation), stmt.final);
}

} // namespace duckdb
