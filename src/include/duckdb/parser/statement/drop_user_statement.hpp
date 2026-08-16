//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/statement/drop_user_statement.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/sql_statement.hpp"

namespace duckdb {

//! DROP USER <name>: remove a login user.
class DropUserStatement : public SQLStatement {
public:
	static constexpr const StatementType TYPE = StatementType::DROP_USER_STATEMENT;

public:
	explicit DropUserStatement(string user_p);

protected:
	DropUserStatement(const DropUserStatement &other) = default;

public:
	unique_ptr<SQLStatement> Copy() const override;
	string ToString() const override;

	//! The name of the user to drop.
	string user;
};

} // namespace duckdb
