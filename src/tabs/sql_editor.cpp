#include <imgui.h>

#include "../table.h"
#include "sql_editor.h"

void sql_editor(State *state) {
	ImGui::PushID("#sql_query");
	ImGui::PushItemWidth(ImGui::GetWindowWidth());
	ImGui::InputTextMultiline("", state->sql_query, sizeof(state->sql_query), ImVec2(0, 0));
	ImGui::PopItemWidth();
	ImGui::PopID();

	if (ImGui::Button("Execute")) {
		bool columns_set = false;
		std::optional<pqxx::result> result = state->db->execute_string(state->sql_query, &state->sql_status);
		state->sql_results.clear();

		if (result.has_value()) {
			state->sql_status.clear();

			if (result->columns()) {
				for (const auto &row : result.value()) {
					std::vector<std::string> fields;

					for (const auto &field : row) {
						if (!columns_set) {
							state->sql_results.columns.push_back(field.name());
						}

						fields.push_back(field.c_str());
					}

					columns_set = true;
					state->sql_results.data.push_back(fields);
				}
			} else {
				state->sql_status = "Success";
			}
		}
	}

	ImGui::Text("%s", state->sql_status.c_str());
	render_table(state->sql_results, "#sql_table");
}
