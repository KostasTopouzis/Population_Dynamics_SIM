#include <SDL3/SDL.h>
#include <SDL3\SDL_log.h>
#include <libs/imgui/backends/imgui_impl_sdlrenderer3.h>
#include <libs/imgui/backends/imgui_impl_sdl3.h>
#include <libs/imgui/imgui.h>
#include <libs/implot/implot.h>
#include <includes/timer_manager.h>
#include <includes/global_state.h>
#include <includes/settings.h>
#include <utils/imgui/u_imgui.h>
#include <utils/implot/u_implot.h>
#include <utils/sdl/u_sdl.h>
#include <iostream>

int main(int argc, char* argv[])
{
	//double test = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;

	int windowWidth = 1500;
	int windowHeight = 500;
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	SDL_PropertiesID props = SDL_CreateProperties();
	if (props == 0) {
		SDL_Log("Unable to create properties: %s", SDL_GetError());
		return -1;
	}

	// SDL window properties
	SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_ALWAYS_ON_TOP_BOOLEAN, false);
	SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN, true);
	SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, true);
	SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_MAXIMIZED_BOOLEAN, true);
	SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, "Bacteria Population Simulation");
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_CENTERED);
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_CENTERED);

	//window = SDL_CreateWindow("SDL3 Test Window!", 0, 0, 0);  
	window = SDL_CreateWindowWithProperties(props);
	if (window == NULL) {
		SDL_Log("Unable to create SDL Window: %s", SDL_GetError());
		return -1;
	}

	//SDL_SetWindowSize(window, windowWidth, windowHeight);
	renderer = SDL_CreateRenderer(window, nullptr);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderClear(renderer);

	ImGui::CreateContext();
	ImPlot::CreateContext();  // Create ImPlot context after ImGui context

	// Set font style
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font = io.Fonts->AddFontFromFileTTF("fonts/static/OpenSans-Regular.ttf", 24.0f);

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);
	io.Fonts->Build();

	//int number = 0;
	float curTime = 0.f;

	bool running = true;

	InitializeData();
	GlobalState::InitializeGlobalState(STARTING_FOOD, STARTING_TEMPERATURE, GlobalState::toxicity, GlobalState::fertility, STARTING_POPULATION, GlobalState::bacteriaType);

	while (running)
	{
		//number++;

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				running = false;
			}
			ImGui_ImplSDL3_ProcessEvent(&event);
		}
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		TimerManager::Update();
		TimerManager::SetTimerByEvent(GlobalState::Update, WORLD_UPDATE_FREQUENCY, TimerManager::elapsedTime);


		// ------------------------------------------------------------------
		// IMGUI WINDOWS
		// ------------------------------------------------------------------

		// Window 1: This window will store a ribbon of options
		DisplayRibbon(font);

		// Window 2: This window displays a plot with Time on the x-axis and Population Size, Food & Temperature on the y-axis
		PrepareData();
		LinePlotTime("Line Graph", "Population Size, Food, and Temperature as a function of Time");

		//if (TimerManager::elapsedTime < 300.0)
		//{
		//	// Prepare data for ImPlot graphs. This function is defined in u_implot.cpp. For testing purposes only
		//	PrepareData(number);
		//	/*test += number;
		//	std::cout << test << std::endl;	*/
		//	LinePlotTime("Line Graph", "Population Size, Food, and Temperature of as a function of time");
		//}


		// Window 3: This window displays running simulation data
		DisplayData(font);

		ImGui::Render();

		SDL_SetRenderDrawColor(renderer, 36, 36, 36, 1);
		SDL_RenderClear(renderer);

		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

		SDL_RenderPresent(renderer);
	}
	ImPlot::DestroyContext();  // Destroy ImPlot context before ImGui context
	CleanUpImGui(); // This wrapper function is defined in u_imgui.cpp
	CleanUpSDL(renderer, window);
	SDL_DestroyProperties(props);

	exit(0);
}