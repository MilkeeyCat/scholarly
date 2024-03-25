#include <imgui.h>

#include "sql_editor.h"
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
		std::sprintf(buf, "tab_%d", tab.data.id);

		if (ImGui::BeginTabItem(buf, &tab.open)) {
			ImGui::Text("Tab: %d", tab.data.id);
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
