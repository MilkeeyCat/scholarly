#include <fstream>

#include "db.h"
#include "utils.h"

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

	conn.prepare("student_avg_estimation_statement", "SELECT AVG(estimation) AS avg FROM estimates WHERE student_id = $1");
	conn.prepare("student_estimates_statement", "SELECT estimation, first_name, last_name, estimates.created_at FROM estimates INNER JOIN teachers ON teachers.id = estimates.teacher_id WHERE estimates.student_id = $1");
	conn.prepare("student_info_statement", "SELECT students.id, first_name, last_name, created_at, groups.name FROM students INNER JOIN groups ON students.group_id = groups.id WHERE students.id = $1;");
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

		StudentCompact student{
			.id = row["id"].as<int>(),
			.first_name = row["first_name"].as<std::string>(),
			.last_name = row["last_name"].as<std::string>(),
			.group = student_group(row["name"].as<const char *>(), row["created_at"].as<const char *>()),
			.est_avg = est_avg};

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

Student Db::student(size_t id) {
	pqxx::work tnx(conn);
	pqxx::row result = tnx.exec_prepared1("student_info_statement", id);
	tnx.commit();
	auto estimates = student_estimates(id);

	return {
		.id = result["id"].as<int>(),
		.first_name = result["first_name"].as<std::string>(),
		.last_name = result["last_name"].as<std::string>(),
		.group = student_group(result["name"].as<const char *>(), result["created_at"].as<const char *>()),
		.created_at = result["created_at"].as<std::string>(),
		.estimates = estimates};
}

std::vector<Estimate> Db::student_estimates(size_t id) {
	pqxx::work tnx(conn);
	pqxx::result result = tnx.exec_prepared("student_estimates_statement", id);
	tnx.commit();

	std::vector<Estimate> estimates;

	for (const auto &row : result) {
		char buf[128];
		std::sprintf(buf, "%s %s", row["first_name"].as<const char *>(), row["last_name"].as<const char *>());

		estimates.push_back(Estimate{
			.estimate = (uint8_t)row["estimation"].as<int>(),
			.created_at = row["created_at"].as<std::string>(),
			.teacher_name = buf});
	}

	return estimates;
}
