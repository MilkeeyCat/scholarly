#include "table.h"
#include <imgui.h>

void render_table(Table table, const char *name) {
	if (table.columns.size()) {
		ImGui::BeginTable(name, table.columns.size(), ImGuiTableFlags_Borders);

		ImGui::TableNextRow();
		for (const std::string column : table.columns) {
			ImGui::TableNextColumn();
			ImGui::TableHeader(column.c_str());
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
