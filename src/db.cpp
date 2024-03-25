#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>

#include "db.h"

StudentCompact StudentCompact::from(pqxx::row &&row) {
	std::istringstream ss(row["created_at"].as<const char *>());
	std::tm tm;
	ss >> std::get_time(&tm, "%Y-%M-%d");

	if (ss.fail()) {
		std::cout << "Failed to parse date string!" << std::endl;
	}

	std::time_t curr_time = std::time(nullptr);
	std::tm *const curr = std::localtime(&curr_time);

	char buf[512];
	std::sprintf(buf, "%d1-%s", curr->tm_year - tm.tm_year, row["name"].as<const char *>());

	return {
		.id = row["id"].as<int>(),
		.first_name = row["first_name"].as<std::string>(),
		.last_name = row["last_name"].as<std::string>(),
		.group = buf};
}

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

	conn.prepare("student_avg_estimation_statement", "SELECT AVG(estimation) AS avg from estimates where student_id = $1");

	students();
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

std::vector<StudentCompact> Db::students() {
	std::vector<StudentCompact> students;

	pqxx::work tnx(conn);
	pqxx::result result = tnx.exec(
		"SELECT students.id, first_name, last_name, created_at, groups.name "
		"FROM students INNER JOIN groups ON "
		"students.group_id = groups.id");
	tnx.commit();

	for (pqxx::row row : result) {
		float est_avg = student_avg_estimation(row["id"].as<size_t>()).value();
		auto student = StudentCompact::from(std::move(row));
		student.est_avg = est_avg;

		students.push_back(student);
	}

	return students;
}

std::optional<float> Db::student_avg_estimation(size_t id) {
	pqxx::work tnx(conn);
	pqxx::row result = tnx.exec_prepared1("student_avg_estimation_statement", id);
	tnx.commit();

	return std::make_optional(result["avg"].as<float>());
}
