#pragma once
#include <libs/imgui/imgui.h>
#include <libs/implot/implot.h>
#include <libs/imgui/backends/imgui_impl_sdlrenderer3.h>
#include <libs/imgui/backends/imgui_impl_sdl3.h>
#include <includes/global_state.h>
#include <includes/settings.h>
#include <includes/timer_manager.h>
#include <utils/imgui/u_imgui.h>
#include <cstdlib>
#include <vector>
#include "constants.h"

/// <summary>
/// Functions and data structures for the u_implot.cpp file
/// </summary>

// Utility Functions for Data Initialization, Preparation and Display
void InitializeData();

void PrepareData();

void DisplayData(ImFont* font);


// Functions for ImGui windows without ImPlot graphs. They will be removed from pushed code
void DisplayRibbon(ImFont* font);   

// Functions for ImGui windows containing ImPlot Graphs
void LinePlotTime(const char* windowTitle, const char* graphTitle);



// ------------------------------------------
// LEGACY FUNCTIONS
// ------------------------------------------

//void FilledLinePlots();

// A simple scrolling data buffer. 
// Kept here for future use in another project
/*
struct ScrollingBuffer {
    int MaxSize;
    std::vector<double> X;
    std::vector<double> Y;

    ScrollingBuffer(int max_size = 5000);

    void AddPoint(double x, double y);
};
*/
