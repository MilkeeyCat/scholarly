#include <ctime>
#include <iomanip>
#include <iostream>

#include "utils.h"

std::string student_group(const char *name, const char *created_at) {
	std::istringstream ss(created_at);
	std::tm tm;
	ss >> std::get_time(&tm, "%Y-%M-%d");

	if (ss.fail()) {
		std::cout << "Failed to parse date string!" << std::endl;
	}

	std::time_t curr_time = std::time(nullptr);
	std::tm *const curr = std::localtime(&curr_time);

	char buf[512];
	std::sprintf(buf, "%d1-%s", curr->tm_year - tm.tm_year, name);

	return std::string(buf);
}
