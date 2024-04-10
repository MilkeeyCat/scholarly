#include "student.h"
#include "../table.h"
#include "imgui.h"

void student_tab(const Student &student) {
	Table table = {
		.columns = {"Estimate", "Subject", "Teacher name", "Created at"}};

	for (const Estimate &estimate : student.estimates) {
		table.data.push_back({std::to_string(estimate.estimate), estimate.subject, estimate.teacher_name, estimate.created_at});
	}

	ImGui::Text("Student id: %d", student.id);
	ImGui::Text("Student name: %s %s", student.first_name.c_str(), student.last_name.c_str());
	ImGui::Text("Student group: %s", student.group.c_str());
	ImGui::Text("Student date of adding in db: %s\n", student.created_at.c_str());
	ImGui::Text("Estimates:");

	render_table(table, "student_estimates");
}
