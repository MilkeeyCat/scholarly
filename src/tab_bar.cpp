#include <imgui.h>

#include "sql_editor.h"
#include "student_tab.h"
#include "students_list.h"
#include "tab_bar.h"

void tab_bar(State *state) {
	ImGui::SetNextWindowPos(ImVec2(0.f, 0.0f));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

	ImGui::Begin("#app", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::BeginTabBar("#app_tab", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_AutoSelectNewTabs);

	if (ImGui::BeginTabItem("Home")) {
		students_list(state);
		ImGui::EndTabItem();
	}
	if (ImGui::BeginTabItem("SQL Editor")) {
		sql_editor(state);
		ImGui::EndTabItem();
	}

	for (size_t i = 0; i < state->tabs.size(); i++) {
		auto tab = state->tabs[i];
		char buf[128];
		std::sprintf(buf, "%s %c.", tab.data.first_name.c_str(), tab.data.last_name[0]);

		if (ImGui::BeginTabItem(buf, &tab.open)) {
			student_tab(tab.data);
			ImGui::EndTabItem();
		}

		// not that pretty but it works xd
		if (!tab.open) {
			state->tabs.erase(state->tabs.begin() + i);
		}
	}

	ImGui::EndTabBar();

	ImGui::End();
}
