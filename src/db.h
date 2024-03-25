#pragma once

#include <pqxx/pqxx>

struct StudentCompact {
	std::string first_name;
	std::string last_name;
	std::string group;
	float est_avg;

	static StudentCompact from(pqxx::row &&row);
};

class Db {
private:
	pqxx::connection conn;

public:
	Db(const char *connect_string);
	void create_tables();
	std::optional<pqxx::result> execute_string(const char *query, char *err);
	std::vector<StudentCompact> students();
	std::optional<float> student_avg_estimation(size_t id);
};
