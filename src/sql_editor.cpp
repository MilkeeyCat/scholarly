#include <cstring>
#include <imgui.h>

#include "sql_editor.h"
#include "table.h"

char buf[512];
char status[512];
bool columns_set = false;
Table table;

void sql_editor(State *state) {
	ImGui::PushID("#sql_query");
	ImGui::PushItemWidth(ImGui::GetWindowWidth());
	ImGui::InputTextMultiline("", buf, sizeof(buf), ImVec2(0, 0));
	ImGui::PopItemWidth();
	ImGui::PopID();

	if (ImGui::Button("Execute")) {
		columns_set = false;
		std::optional<pqxx::result> result = state->db->execute_string(buf, status);

		if (result.has_value()) {
			table.clear();
			memset(status, 0, sizeof(status));

			if (result->columns()) {
				for (const auto &row : result.value()) {
					std::vector<std::string> fields;

					for (const auto &field : row) {
						if (!columns_set) {
							table.columns.push_back(field.name());
						}

						fields.push_back(field.c_str());
					}

					columns_set = true;
					table.data.push_back(fields);
				}
			} else {
				const char *msg = "Success";
				memcpy(status, msg, strlen(msg));
			}
		}
	}

	if (strlen(status) > 0 && strcmp("Success", status)) {
		table.clear();
	}

	ImGui::Text("%s", status);

	if (table.columns.size()) {
		ImGui::BeginTable("#sql_table", table.columns.size(), ImGuiTableFlags_Borders);

		ImGui::TableNextRow();
		for (const std::string column : table.columns) {
			ImGui::TableNextColumn();
			ImGui::Text("%s", column.c_str());
		}

		for (const auto &rows : table.data) {
			ImGui::TableNextRow();
			for (const auto &field : rows) {
				ImGui::TableNextColumn();
				ImGui::Text("%s", field.c_str());
			}
		}

		ImGui::EndTable();
	}
}
