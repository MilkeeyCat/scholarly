#include <imgui.h>

#include "sql_editor.h"
#include "students_list.h"
#include "tab_bar.h"

void tab_bar(State *state) {
	ImGui::SetNextWindowPos(ImVec2(0.f, 0.0f));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

	ImGui::Begin("#kek", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::BeginTabBar("#owo", ImGuiTabBarFlags_Reorderable);

	if (ImGui::BeginTabItem("Home")) {
		students_list(state);
		ImGui::EndTabItem();
	}
	if (ImGui::BeginTabItem("SQL Editor")) {
		sql_editor(state);
		ImGui::EndTabItem();
	}

	ImGui::EndTabBar();

	ImGui::End();
}
