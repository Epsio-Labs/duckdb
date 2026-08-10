#include "duckdb/parser/statement/create_user_statement.hpp"
#include "duckdb/planner/binder.hpp"
#include "duckdb/planner/operator/logical_create_user.hpp"

namespace duckdb {

BoundStatement Binder::Bind(CreateUserStatement &stmt) {
	BoundStatement result;
	result.types = {LogicalType::BOOLEAN};
	result.names = {"Success"};

	result.plan = make_uniq<LogicalCreateUser>(stmt.user, stmt.has_password, stmt.password);

	auto &properties = GetStatementProperties();
	properties.return_type = StatementReturnType::NOTHING;
	return result;
}

} // namespace duckdb
