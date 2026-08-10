//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/operator/logical_create_user.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/planner/logical_operator.hpp"

namespace duckdb {

//! CREATE USER <name> [PASSWORD '<password>']: add a login user.
//! The engine consuming the plan creates the user; DuckDB itself only binds
//! the statement, so this operator has no physical counterpart.
class LogicalCreateUser : public LogicalOperator {
public:
	static constexpr const LogicalOperatorType TYPE = LogicalOperatorType::LOGICAL_CREATE_USER;

public:
	LogicalCreateUser(string user_p, bool has_password_p, string password_p)
	    : LogicalOperator(LogicalOperatorType::LOGICAL_CREATE_USER), user(std::move(user_p)),
	      has_password(has_password_p), password(std::move(password_p)) {
	}

	//! The name of the user to create.
	string user;
	//! Whether a PASSWORD clause was given; without one the user authenticates by trust.
	bool has_password;
	//! The password, meaningful only when has_password is set.
	string password;

public:
	idx_t EstimateCardinality(ClientContext &context) override {
		return 1;
	}

protected:
	void ResolveTypes() override {
		types.emplace_back(LogicalType::BOOLEAN);
	}
};

} // namespace duckdb
