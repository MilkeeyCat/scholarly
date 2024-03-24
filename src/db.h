#pragma once

#include <pqxx/pqxx>

class Db {
private:
	pqxx::connection conn;

public:
	Db(const char *connect_string);
	void create_tables();
	std::optional<pqxx::result> execute_string(const char *query, char *err);
};
