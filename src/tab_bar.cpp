#include <imgui.h>

#include "sql_editor.h"
#include "tab_bar.h"

void tab_bar(State *state) {
	ImGui::SetNextWindowPos(ImVec2(0.f, 0.0f));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

	ImGui::Begin("#kek", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::BeginTabBar("#owo", ImGuiTabBarFlags_Reorderable);

	if (ImGui::BeginTabItem("Home")) {
		ImGui::Text("HEY");
		ImGui::EndTabItem();
	}
	if (ImGui::BeginTabItem("SQL Editor")) {
		sql_editor(state);
		ImGui::EndTabItem();
	}

	ImGui::EndTabBar();

	ImGui::End();
}
