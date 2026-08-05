#include "duckdb/parser/transformer.hpp"
#include "duckdb/parser/statement/call_statement.hpp"
#include "duckdb/parser/expression/function_expression.hpp"
#include "duckdb/parser/expression/constant_expression.hpp"

namespace duckdb {

unique_ptr<SQLStatement> Transformer::TransformCompact(duckdb_libpgquery::PGCompactStmt &stmt) {
	// Rewrite into "CALL compact(catalog, schema, table, final)", the same
	// route CHECKPOINT takes: the table function machinery carries the
	// statement to the engine without a dedicated logical operator. Absent
	// name parts travel as empty strings so the argument shape is fixed.
	vector<unique_ptr<ParsedExpression>> children;
	auto part = [](const char *value) {
		return make_uniq<ConstantExpression>(Value(value ? value : ""));
	};
	children.push_back(part(stmt.relation->catalogname));
	children.push_back(part(stmt.relation->schemaname));
	children.push_back(part(stmt.relation->relname));
	children.push_back(make_uniq<ConstantExpression>(Value::BOOLEAN(stmt.final)));

	auto result = make_uniq<CallStatement>();
	result->function = make_uniq<FunctionExpression>("compact", std::move(children));
	return std::move(result);
}

} // namespace duckdb
