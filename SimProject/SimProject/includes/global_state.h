#pragma once
#include <includes/population_control_enums.h>
#include <includes/entity.h>
#include <vector>

namespace GlobalState
{
	//temporary for debug
	extern int optimalTemperature; 
	extern int maturedPopulation;
	extern uint8_t prematuredDeaths;
	extern BacteriaTempType bacteriaType;
	//This changes based on temperature the further away from optimal temp the more
	//resources they need and take(default is 1).
	extern int requiredEnergy;   
	extern int32_t food; 
	extern int8_t temperature;  
	extern ToxicityLevel toxicity; 
	extern Fertility fertility;  
	extern std::vector<Entity> initialPopulation; 
	extern std::vector<Entity> livingPopulation;   
	/// <summary>
	/// Initializes the starting conditions of the simulation 
	/// </summary>
	/// <param name="food:">Main resource that all entities depend on</param>
	/// <param name="temperature:">Enviromental factors that affect the entities on a global Scale</param>
	/// <param name="toxicity"></param>
	/// <param name="fertility"></param>
	void InitializeGlobalState(uint32_t food, int8_t temperature, ToxicityLevel toxicity, Fertility fertility, uint32_t  startingPopulation, BacteriaTempType tempType);
	/// <summary>
	/// Main function to update all variables
	/// </summary>
	int GetPopulation();  

	void Update();

	//void ManageMaturity();

	void ManageEnergy(); 
	void ManageHealth();
	void ManageGraduation();
	void ManageDeath(const uint32_t index); 
	void ManageDecay(Entity& entity);   
	void ManageStates();
	void ManageDivision(Entity& entity);
	int  GetPrematureDeaths(); 
	void WipePopulation();
	void GrowFood();
	void EndSimulation();
	void CalculateNeededEnergy(); 
	void ConsoleHelper();
	void SetOptimalTemperature(); 
}
