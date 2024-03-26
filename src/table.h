#pragma once

#include <string>
#include <vector>

struct Table {
	std::vector<std::string> columns;
	std::vector<std::vector<std::string>> data;

	void clear() {
		columns.clear();
		data.clear();
	}
};
