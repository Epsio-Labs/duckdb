#include "duckdb/parser/statement/drop_user_statement.hpp"
#include "duckdb/planner/binder.hpp"
#include "duckdb/planner/operator/logical_drop_user.hpp"

namespace duckdb {

BoundStatement Binder::Bind(DropUserStatement &stmt) {
	BoundStatement result;
	result.types = {LogicalType::BOOLEAN};
	result.names = {"Success"};

	result.plan = make_uniq<LogicalDropUser>(stmt.user);

	auto &properties = GetStatementProperties();
	properties.return_type = StatementReturnType::NOTHING;
	return result;
}

} // namespace duckdb
