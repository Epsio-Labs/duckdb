//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/statement/create_user_statement.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/sql_statement.hpp"

namespace duckdb {

//! CREATE USER <name> [PASSWORD '<password>']: add a login user.
class CreateUserStatement : public SQLStatement {
public:
	static constexpr const StatementType TYPE = StatementType::CREATE_USER_STATEMENT;

public:
	CreateUserStatement(string user_p, bool has_password_p, string password_p);

protected:
	CreateUserStatement(const CreateUserStatement &other) = default;

public:
	unique_ptr<SQLStatement> Copy() const override;
	string ToString() const override;

	//! The name of the user to create.
	string user;
	//! Whether a PASSWORD clause was given; without one the user authenticates by trust.
	bool has_password;
	//! The password, meaningful only when has_password is set.
	string password;
};

} // namespace duckdb
