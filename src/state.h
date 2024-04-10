#pragma once

#include "db.h"
#include "table.h"

template<typename T>
struct Tab {
	bool open;
	T data;
};

struct State {
	Db *db;
	std::vector<Tab<Student>> tabs;
	Table sql_results;
	std::string sql_status;
	char sql_query[512];
};
