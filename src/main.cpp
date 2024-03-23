#include "component.h"
#include "components/list.h"
#include "db.h"
#include "state.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int main() {
	if (!glfwInit()) {
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window =
		glfwCreateWindow(1280, 720, "Little C++ program to manage data from Postgresqueal", nullptr, nullptr);

	if (window == nullptr) {
		return 1;
	}

	glfwMakeContextCurrent(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |=
		ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |=
		ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	Db db("postgresql://postgres:root@localhost:5432/students");
	State state = {
		.page = Page::Main};

	List list;

	Component *components[] = {
		&list};

	for (Component *component : components) {
		component->state = &state;
	}

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

		for (Component *component : components) {
			component->render();
		}

		ImGui::Render();
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	return 0;
}
