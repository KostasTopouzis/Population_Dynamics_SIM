#pragma once
#include <vector>

// ==========================================
// CONSTANTS FOR THE U_IMPLOT.CPP FILE
// ==========================================

namespace UImPlot {

    inline std::vector<double> time_vec;
    inline std::vector<double> food_vec; // Ranges: [0,100]
    inline std::vector<double> temperature_vec; // Ranges: [-100,200]
    inline std::vector<double> populationSize_vec; // Ranges (in thousands): [0, 1000]

    inline int currentFood;
	inline int currentTemperature;
	inline int currentPopulationSize;

    inline constexpr double timeMin = 0.0;
    inline constexpr double timeMax = 60.0;
    inline constexpr double foodMin = 5.0;
    inline constexpr double foodMax = 90.0;
    inline constexpr double temperatureMin = -80.0;
    inline constexpr double temperatureMax = 180.0;
    inline constexpr double populationMin = 10;
    inline constexpr double populationMax = 500;

	inline constexpr double windowSize = 20.0;
}
