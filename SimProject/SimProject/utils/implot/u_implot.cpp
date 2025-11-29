#include "u_implot.h"
#include <iostream>

#define X_AXIS_1 "Time (s)"
#define Y_AXIS_1 "Population Size"
#define Y_AXIS_2 "Temperature"
#define Y_AXIS_3 "Food"


// ---------------------------------
// Utility Functions
// ---------------------------------

// InitializeData function that uses global vectors to initialize the data
void InitializeData() {
    UImPlot::time_vec = { 0.0 };
    UImPlot::food_vec = { 50.0 };
    UImPlot::temperature_vec = { 40.0 };
    UImPlot::populationSize_vec = { 200.0 };

    UImPlot::time_vec.reserve(100000);
    UImPlot::food_vec.reserve(100000);
    UImPlot::temperature_vec.reserve(100000);
    UImPlot::populationSize_vec.reserve(100000);
}


// PrepareData function that uses global vectors
void PrepareData() {
    double newFood = static_cast<double>(GlobalState::food);
    double newTemperature = static_cast<double>(GlobalState::temperature);
    double newPopulationSize = static_cast<double>(GlobalState::livingPopulation.size());
    double t = static_cast<double>(TimerManager::elapsedTime);

    if (t <= UImPlot::time_vec.back()) {
        // non-increasing time: skip or set t = time_vec.back() + tiny_eps
        t = UImPlot::time_vec.back() + 1e-6;
    }
    UImPlot::time_vec.push_back(t);

    // Push back the newly computed values
    UImPlot::food_vec.push_back(newFood);
    UImPlot::temperature_vec.push_back(newTemperature);
    UImPlot::populationSize_vec.push_back(newPopulationSize);
}


// ---------------------------------
// Functions for ImPlot Graphs
// ---------------------------------


void LinePlotTime(const char* windowTitle, const char* graphTitle) {
    ImGui::PushStyleColor(ImGuiCol_WindowBg, graphWindowBgColor);
    ImGui::Begin(windowTitle);
    static bool y2_axis = true;
    static bool y3_axis = true;

    // Set a window of given size for the x-axis
    // This changes window every 20 secs
	double x_min = (int)(UImPlot::time_vec.back() / UImPlot::windowSize) * UImPlot::windowSize;
    // This follows the line as it moves retaining a window of 20 secs
    //double x_min = (time_vec.back() > UImPlot::windowSize) ? (time_vec.back() - UImPlot::windowSize) : 0.0;
    double x_max = x_min + UImPlot::windowSize;

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));  // RGB E6E9F5
    ImGui::Text("Toggle Y-Axes:");
    ImGui::Checkbox(Y_AXIS_2, &y2_axis);
    ImGui::SameLine();
    ImGui::Checkbox(Y_AXIS_3, &y3_axis);
    
    ImGui::BulletText("You can drag axes to the opposite side of the plot.");
    ImGui::BulletText("Hover over legend items to see which axis they are plotted on.");
    
    ImGui::PopStyleColor();
    int n = static_cast<int>(UImPlot::time_vec.size());
    if (ImPlot::BeginPlot(graphTitle, ImVec2(-1, 600))) {
        ImPlot::SetupAxes(X_AXIS_1, Y_AXIS_1);
        ImPlot::SetupAxesLimits(x_min, x_max, 0.0, UImPlot::populationMax, ImGuiCond_Always);
                
        if (y2_axis) {
            ImPlot::SetupAxis(ImAxis_Y2, Y_AXIS_2, ImPlotAxisFlags_AuxDefault);
            ImPlot::SetupAxisLimits(ImAxis_Y2, -100.0, 200.0);
        }
        if (y3_axis) {
            ImPlot::SetupAxis(ImAxis_Y3, Y_AXIS_3, ImPlotAxisFlags_AuxDefault);
            ImPlot::SetupAxisLimits(ImAxis_Y3, 0.0, 100.0);
        }

        if (n > 1) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            ImPlot::PlotLine("Population Size", UImPlot::time_vec.data(), UImPlot::populationSize_vec.data(), n);
            if (y2_axis) {
                ImPlot::SetAxes(ImAxis_X1, ImAxis_Y2);
                ImPlot::PlotLine("Temperature", UImPlot::time_vec.data(), UImPlot::temperature_vec.data(), n);
            }
            if (y3_axis) {
                ImPlot::SetAxes(ImAxis_X1, ImAxis_Y3);
                ImPlot::PlotLine("Food", UImPlot::time_vec.data(), UImPlot::food_vec.data(), n);
            }
        ImGui::PopStyleColor();
        ImPlot::EndPlot();
        }
    }
    ImGui::PopStyleColor();
    ImGui::End();
    //int pops = (n > 1 ? 3 : 2);
}



// ------------------------------------------
// DISPLAY DATA FUNCTIONS
// ------------------------------------------

// DisplayData function that uses the global vectors to display the data
void DisplayData(ImFont* font) {
    // Running display analysis: 
	// population size: 10, food: 5, temperature: 0.1

    ImGui::PushStyleColor(ImGuiCol_WindowBg, dataWindowBgColor); // RGB F5F2E6
    ImGui::Begin("Simulation Parameters");
    if (font) // Check if the font was loaded successfully
    {
        // Push the large font onto the style stack
        ImGui::PushFont(font);

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
        ImGui::NewLine();
        ImGui::Text("Elapsed time : %.2f ", TimerManager::elapsedTime);
        ImGui::NewLine();
        ImGui::Text("Total Population Size (in thousands): %d", (int)(UImPlot::populationSize_vec.back() / 10) * 10);
        ImGui::NewLine();
        ImGui::Text("Total Food Resources: %d", (int)(UImPlot::food_vec.back() / 5) * 5);
        ImGui::NewLine();
        ImGui::Text("Environment Temperature (Celsius): %.1f ", (int)(UImPlot::temperature_vec.back() / 0.5) * 0.5);
        ImGui::PopStyleColor();
    }
    ImGui::PopFont();
    ImGui::PopStyleColor();
    ImGui::End();
}

void DisplayRibbon(ImFont* font) {
    ImGui::PushStyleColor(ImGuiCol_WindowBg, menuWindowBgColor); // Set window background to red
    ImGui::Begin("Simulation Parameters Ribbon");
    if (font)
    {
        ImGui::PushFont(font);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
		ImGui::Button("Options", ImVec2(100, 30));
        ImGui::PopStyleColor();
    }
    ImGui::PopFont();
    ImGui::End();
	ImGui::PopStyleColor();
}

// ------------------------------------------
// TESTING FUNCTIONS
// ------------------------------------------

// PrepareData function that uses the global arrays to prepare the data. For testing only
/*
void PrepareData() {
    srand(0);
    for (int i = 1; i < 3600; ++i) {
        time[i] = (double)i;
        food[i] = food[i - 1] + RandomRange(-10.0, 10.0);
        temperature[i] = temperature[i - 1] + RandomRange(-20.0, 20.0);
        populationSize[i] = populationSize[i - 1] + (food[i] - food[i - 1]) * RandomRange(5.0, 10.0) - (temperature[i] - temperature[i - 1]) * RandomRange(0.5, 1.0);
    }
}
*/


// ---------------------------------------
// LEGACY FUNCTIONS
// ---------------------------------------

/*
void FilledLinePlots() {
    static double xs1[60], ys1[60], ys2[60], ys3[60];
    srand(0);
    for (int i = 0; i < 60; ++i) {
        xs1[i] = (float)i;
        ys1[i] = RandomRange(150.0, 450.0);
        ys2[i] = ys1[i] * RandomRange(0.4, 0.9);
    }

    static bool show_lines = true;
    static bool show_fills = true;
    static float fill_ref = 0;
    static int shade_mode = 0;
    static ImPlotShadedFlags flags = 0;
    ImGui::Checkbox("Lines", &show_lines); ImGui::SameLine();
    ImGui::Checkbox("Fills", &show_fills);
    if (show_fills) {
        ImGui::SameLine();
        if (ImGui::RadioButton("To -INF", shade_mode == 0))
            shade_mode = 0;
        ImGui::SameLine();
        if (ImGui::RadioButton("To +INF", shade_mode == 1))
            shade_mode = 1;
        ImGui::SameLine();
        if (ImGui::RadioButton("To Ref", shade_mode == 2))
            shade_mode = 2;
        if (shade_mode == 2) {
            ImGui::SameLine();
            ImGui::SetNextItemWidth(100);
            ImGui::DragFloat("##Ref", &fill_ref, 1, -100, 500);
        }
    }

    if (ImPlot::BeginPlot("Population & Food Levels")) {
        ImPlot::SetupAxes("Seconds", "Food/Population");
        ImPlot::SetupAxesLimits(0, 100, 0, 500);
        if (show_fills) {
            ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
            ImPlot::PlotShaded("Population", xs1, ys2, 60, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref, flags);
            ImPlot::PlotShaded("Food", xs1, ys1, 60, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref, flags);
            ImPlot::PopStyleVar();
        }
        if (show_lines) {
            ImPlot::PlotLine("Population", xs1, ys2, 60);
            ImPlot::PlotLine("Food", xs1, ys1, 60);

        }
        ImPlot::EndPlot();
    }
}
*/

/*
void PrepareData(int i) {
    static bool seeded = false;
    if (!seeded) {
        srand(UImPlot::time_vec[0]);  // Use current time as seed for randomness
        seeded = true;
    }

    // Ensure indices are valid and avoid accessing out-of-bounds
    if (i <= 0 || UImPlot::food_vec.size() <= 0 || UImPlot::temperature_vec.size() <= 0 || UImPlot::populationSize_vec.size() <= 0)
        return;  // Early exit if indices are invalid

    // Push back updated values with proper handling of overflow
    double previousFood = UImPlot::food_vec.back();
    double previousTemperature = UImPlot::temperature_vec.back();
    double previousPopulation = UImPlot::populationSize_vec.back();

    // Adding randomness to the food and temperature vectors
    double foodChange = RandomRange(-1.0, 1.0);
    double temperatureChange = RandomRange(-2.0, 2.0);

    // Update vectors with random changes
    double newFood = previousFood + foodChange;
    double newTemperature = previousTemperature + temperatureChange;

    // Population size change depends on food and temperature differences
    double foodEffectFactor = RandomRange(0.1, 1.0);
    double temperatureEffectFactor = RandomRange(0.5, 2.0);
    double populationChange = (foodChange)*foodEffectFactor
        - (temperatureChange)*temperatureEffectFactor;

    double newPopulationSize = previousPopulation + populationChange;

    // For debugging: print intermediate values every 100 iterations

    // Clamp values (for limits see constants.h)
    newFood = std::max(UImPlot::foodMin, std::min(UImPlot::foodMax, newFood));
    newTemperature = std::max(UImPlot::temperatureMin, std::min(UImPlot::temperatureMax, newTemperature));
    newPopulationSize = std::max(UImPlot::populationMin, newPopulationSize);

    double t = static_cast<double>(TimerManager::elapsedTime);
    if (t <= UImPlot::time_vec.back()) {
        // non-increasing time: skip or set t = time_vec.back() + tiny_eps
        t = UImPlot::time_vec.back() + 1e-6;
    }

    // Push back the newly computed values
    UImPlot::time_vec.push_back(t);
    UImPlot::food_vec.push_back(newFood);
    UImPlot::temperature_vec.push_back(newTemperature);
    UImPlot::populationSize_vec.push_back(newPopulationSize);
    */

/* Utility function to generate random numbers in a range
template <typename T>
inline T RandomRange(T min, T max) {
    T scale = rand() / (T)RAND_MAX;
    return min + scale * (max - min);
}
*/