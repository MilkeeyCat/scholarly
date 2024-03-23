#include <fstream>
#include <iostream>
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
