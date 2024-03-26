#include "students_list.h"
#include "../db.h"
#include "imgui.h"
#include "../state.h"

#define HEIGHT 150

void compact_student(State *state, const StudentCompact &student) {
	auto s = ImGui::GetCursorPos();
	ImVec2 end(200, s.y + HEIGHT);

	ImGui::Text("Name %s %s", student.first_name.c_str(), student.last_name.c_str());
	ImGui::Text("Grop: %s", student.group.c_str());
	ImGui::Text("Avg estimation: %.2f", student.est_avg);
	ImGui::PushID(student.first_name.c_str());

	char buf[128];
	std::sprintf(buf, "search_result_%d", student.id);

	if (ImGui::Button("More info")) {
		bool exist = false;

		for (const auto &tab : state->tabs) {
			if (tab.data.id == student.id) {
				exist = true;
				break;
			}
		}

		if (!exist) {
			state->tabs.push_back(
				{.open = true,
					.data = state->db->student(student.id)});
		}
	}

	ImGui::PopID();
	ImGui::SetCursorPosY(end.y);
}

void students_list(State *state) {
	std::vector<StudentCompact> students = state->db->students();

	ImGui::BeginChild("#students_search_result");
	for (const auto &student : students) {
		compact_student(state, student);
	}
	ImGui::EndChild();
}
