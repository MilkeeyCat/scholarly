#pragma once

#include <pqxx/pqxx>

struct Estimate {
	uint8_t estimate;
	std::string created_at;
	std::string teacher_name;
	std::string subject;
};

struct Student {
	int id;
	std::string first_name;
	std::string last_name;
	std::string group;
	std::string created_at;
	std::vector<Estimate> estimates;
};

struct StudentCompact {
	int id;
	std::string first_name;
	std::string last_name;
	std::string group;
	float est_avg;
};

class Db {
private:
	pqxx::connection conn;

public:
	Db(const char *connect_string);
	void create_tables();
	std::optional<pqxx::result> execute_string(const char *query, std::string *err);
	std::vector<StudentCompact> students();
	std::optional<float> student_avg_estimation(size_t id);
	Student student(size_t id);
	std::vector<Estimate> student_estimates(size_t id);
};
