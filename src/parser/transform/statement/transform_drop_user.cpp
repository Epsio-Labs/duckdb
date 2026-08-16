#include "duckdb/parser/statement/drop_user_statement.hpp"
#include "duckdb/parser/transformer.hpp"

namespace duckdb {

unique_ptr<SQLStatement> Transformer::TransformDropUser(duckdb_libpgquery::PGDropUserStmt &stmt) {
	return make_uniq<DropUserStatement>(stmt.user);
}

} // namespace duckdb
