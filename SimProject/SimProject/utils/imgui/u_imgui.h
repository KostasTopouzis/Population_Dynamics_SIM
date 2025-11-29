#include "imgui.h"
#include "imgui_impl_sdlrenderer3.h"
#include "imgui_impl_sdl3.h"

// Definitions of functions for the u_imgui.cpp, u_implot.h, and u_implot.cpp files

// Window styling
extern ImVec4 graphWindowBgColor;
extern ImVec4 menuWindowBgColor;
extern ImVec4 dataWindowBgColor;




//ImVec4 graphWindowBgColor;
//ImVec4 dataWindowBgColor;
//ImVec4 menuWindowBgColor;

void setStyling();


// Wrapper functions
void CleanUpImGui(); 


// Test functions
void ImGuiTest(float deltaTime);
