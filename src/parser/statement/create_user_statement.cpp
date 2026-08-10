#include "duckdb/parser/statement/create_user_statement.hpp"

namespace duckdb {

CreateUserStatement::CreateUserStatement(string user_p, bool has_password_p, string password_p)
    : SQLStatement(StatementType::CREATE_USER_STATEMENT), user(std::move(user_p)), has_password(has_password_p),
      password(std::move(password_p)) {
}

unique_ptr<SQLStatement> CreateUserStatement::Copy() const {
	return unique_ptr<CreateUserStatement>(new CreateUserStatement(*this));
}

string CreateUserStatement::ToString() const {
	string result = "CREATE USER " + user;
	if (has_password) {
		result += " PASSWORD [redacted]";
	}
	return result;
}

} // namespace duckdb
