#include <cstring>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

#include "db.h"

Db::Db(const char *connect_string) :
	conn(pqxx::connection(connect_string)) {
	pqxx::work tnx(conn);

	bool exists = tnx.query_value<bool>(
		"SELECT EXISTS ("
		"SELECT 1 "
		"FROM pg_tables "
		"WHERE schemaname = 'public' "
		"AND tablename = 'students')");

	tnx.commit();

	if (!exists) {
		create_tables();
	}
}

void Db::create_tables() {
	std::ifstream stream("../tables.sql");
	std::stringstream buffer;
	buffer << stream.rdbuf();

	pqxx::work tnx(conn);
	pqxx::result result = tnx.exec(buffer.str());
	tnx.commit();
}

std::optional<pqxx::result> Db::execute_string(const char *query, char *err) {
	try {
		pqxx::work tnx(conn);
		pqxx::result result = tnx.exec(query);
		tnx.commit();

		return result;
	} catch (pqxx::sql_error &e) {
		const char *what = e.what();
		memcpy(err, what, strlen(what));

		return std::nullopt;
	}
}
