#include "duckdb/parser/statement/create_user_statement.hpp"
#include "duckdb/parser/transformer.hpp"

namespace duckdb {

unique_ptr<SQLStatement> Transformer::TransformCreateUser(duckdb_libpgquery::PGCreateUserStmt &stmt) {
	bool has_password = stmt.password != nullptr;
	return make_uniq<CreateUserStatement>(stmt.user, has_password, has_password ? stmt.password : "");
}

} // namespace duckdb
