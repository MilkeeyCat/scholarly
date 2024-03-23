#include "list.h"
#include "imgui.h"

void List::render() {
	if (state->page == Page::Main) {
		ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::Text("Hello from list component UwU");
		ImGui::End();
	}
}
