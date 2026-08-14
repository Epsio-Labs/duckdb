#include "catch.hpp"
#include "duckdb.hpp"
#include "duckdb/catalog/catalog_search_path.hpp"
#include "duckdb/common/constants.hpp"
#include "duckdb/main/client_data.hpp"

using namespace duckdb;

TEST_CASE("Explicit attached pg_catalog precedes the system catalog", "[catalog]") {
	DuckDB database(nullptr);
	Connection connection(database);
	auto &search_path = *ClientData::Get(*connection.context).catalog_search_path;
	vector<CatalogSearchEntry> entries;
	entries.emplace_back("remote", DEFAULT_SCHEMA);
	entries.emplace_back("remote", "pg_catalog");

	search_path.Set(std::move(entries), CatalogSetPathType::SET_DIRECTLY);
	auto pg_catalogs = search_path.GetCatalogsForSchema("pg_catalog");
	auto information_schema_catalogs = search_path.GetCatalogsForSchema("information_schema");

	REQUIRE(pg_catalogs == vector<string> {"remote", SYSTEM_CATALOG});
	REQUIRE(information_schema_catalogs == vector<string> {SYSTEM_CATALOG});
}
