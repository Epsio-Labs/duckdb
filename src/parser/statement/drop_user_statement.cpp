#include "duckdb/parser/statement/drop_user_statement.hpp"

namespace duckdb {

DropUserStatement::DropUserStatement(string user_p)
    : SQLStatement(StatementType::DROP_USER_STATEMENT), user(std::move(user_p)) {
}

unique_ptr<SQLStatement> DropUserStatement::Copy() const {
	return unique_ptr<DropUserStatement>(new DropUserStatement(*this));
}

string DropUserStatement::ToString() const {
	return "DROP USER " + user;
}

} // namespace duckdb
