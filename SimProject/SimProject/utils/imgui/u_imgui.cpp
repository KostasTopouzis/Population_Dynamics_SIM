#include <utils/imgui/u_imgui.h>

ImVec4 graphWindowBgColor(0.89f, 0.91f, 0.95f, 1.0f);
ImVec4 menuWindowBgColor(0.90f, 0.88f, 0.83f, 1.0f);
ImVec4 dataWindowBgColor(0.95f, 0.94f, 0.89f, 1.0f);

void setStyling()
{
	// 1. Get a reference to the global style
	ImGuiStyle& style = ImGui::GetStyle();

	// 2. Define your color (Red, Green, Blue, Alpha)
	// Let's make a dark grey color
	/*ImVec4 graphWindowBgColor(0.89f, 0.91f, 0.95f, 1.0f);
	ImVec4 menuWindowBgColor(0.90f, 0.88f, 0.83f, 1.0f);
	ImVec4 dataWindowBgColor(0.95f, 0.94f, 0.89f, 1.0f);*/

	// 3. Assign it to the WindowBg index
	//style.Colors[ImGuiCol_WindowBg] = customBgColor;

	// Optional: You can also change floats directly
	//style.WindowRounding = 5.0f;
}


void CleanUpImGui()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiTest(float deltaTime)
{
	ImGui::Begin("Bacteria Population Simulation");
	ImGui::Text("");
	ImGui::Text("");
	ImGui::NewLine();
	ImGui::Text("elapsed time : %.2f ", deltaTime);
	ImGui::Button("label", { 100,20 });
	ImGui::End();
}
