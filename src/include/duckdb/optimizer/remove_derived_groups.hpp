//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/optimizer/remove_derived_groups.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/optimizer/column_binding_replacer.hpp"
#include "duckdb/planner/logical_operator.hpp"

namespace duckdb {

class Optimizer;

//! The RemoveDerivedGroups optimizer removes GROUP BY keys that are functionally determined by other GROUP BY keys.
//! For example, in
//!     GROUP BY ClientIP, ClientIP - 1, ClientIP - 2, ClientIP - 3
//! the last three keys are deterministic functions of ClientIP, so they take a single value within each ClientIP
//! group: grouping by them adds nothing. We drop such keys from the aggregate (shrinking the grouping key) and
//! recompute them in a projection placed directly above the aggregate, then rewire the bindings of the operators
//! above so they read the recomputed values.
class RemoveDerivedGroups {
public:
	explicit RemoveDerivedGroups(Optimizer &optimizer);

	//! Rewrite the plan, removing derived groups wherever possible
	unique_ptr<LogicalOperator> Optimize(unique_ptr<LogicalOperator> op);

private:
	//! A column-binding remap to apply once the whole tree has been rewritten. The bindings of the operators above
	//! the inserted projection (`stop`) must be redirected from the old aggregate outputs to the projection.
	struct PendingRemap {
		vector<ReplacementBinding> bindings;
		//! The inserted projection: the replacer must not recurse into it (it legitimately reads the aggregate)
		LogicalOperator *stop;
	};

	unique_ptr<LogicalOperator> RewritePlan(unique_ptr<LogicalOperator> op);
	//! Rewrite a single aggregate. Returns Projection(Aggregate) if any group was removed, else `op` unchanged.
	unique_ptr<LogicalOperator> RewriteAggregate(unique_ptr<LogicalOperator> op);

	Optimizer &optimizer;
	vector<PendingRemap> pending_remaps;
};

} // namespace duckdb
