#include <imgui.h>

#include "sql_editor.h"

char buf[512];
std::string result;

void sql_editor(State *state) {
	ImGui::PushID("#sql_query");
	ImGui::PushItemWidth(ImGui::GetWindowWidth());
	ImGui::InputTextMultiline("", buf, sizeof(buf), ImVec2(0, 0));
	ImGui::PopItemWidth();
	ImGui::PopID();

	if (ImGui::Button("Execute")) {
		std::optional<std::string> res = state->db->execute_string(buf);

		if (res.has_value()) {
			result = std::move(res.value());
		} else {
			result = "Success";
		}
	}

	ImGui::Text("%s", result.data());
}
