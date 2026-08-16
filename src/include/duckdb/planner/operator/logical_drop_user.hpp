//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/operator/logical_drop_user.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/planner/logical_operator.hpp"

namespace duckdb {

//! DROP USER <name>: remove a login user.
//! The engine consuming the plan drops the user; DuckDB itself only binds
//! the statement, so this operator has no physical counterpart.
class LogicalDropUser : public LogicalOperator {
public:
	static constexpr const LogicalOperatorType TYPE = LogicalOperatorType::LOGICAL_DROP_USER;

public:
	explicit LogicalDropUser(string user_p)
	    : LogicalOperator(LogicalOperatorType::LOGICAL_DROP_USER), user(std::move(user_p)) {
	}

	//! The name of the user to drop.
	string user;

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
