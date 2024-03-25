#pragma once

#include "db.h"

template<typename T>
struct Tab {
	bool open;
	T data;
};

struct State {
	Db *db;
	std::vector<Tab<Student>> tabs;
};
