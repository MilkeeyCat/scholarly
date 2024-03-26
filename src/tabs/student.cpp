#include "student.h"
#include "imgui.h"

void student_tab(const Student &student) {
	ImGui::Text("Student id: %d", student.id);
	ImGui::Text("Student name: %s %s", student.first_name.c_str(), student.last_name.c_str());
	ImGui::Text("Student group: %s", student.group.c_str());
	ImGui::Text("Student date of adding in db: %s", student.created_at.c_str());
}
