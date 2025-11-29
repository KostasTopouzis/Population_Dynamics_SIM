#include <includes/global_state.h>
#include <stdio.h>
#include <includes/settings.h>
#include <includes/timer_manager.h>

namespace GlobalState
{
	int optimalTemperature = 0;
	int maturedPopulation = 0;
	int requiredEnergy = 1;
	BacteriaTempType bacteriaType = BacteriaTempType::MESOPHILES;
	uint8_t prematuredDeaths = 0;  
	int32_t  food = 0; 
	int8_t temperature = 0; 
	ToxicityLevel toxicity = ToxicityLevel::DISABLED;  
	Fertility fertility = Fertility::DISABLED;
	std::vector<Entity> initialPopulation;
	std::vector<Entity> livingPopulation;
}

void GlobalState::InitializeGlobalState(uint32_t food, int8_t temperature, ToxicityLevel toxicity, Fertility fertility,uint32_t  startingPopulation, BacteriaTempType tempType)
{
	GlobalState::food = food; 
	GlobalState::temperature = temperature;
	GlobalState::toxicity = toxicity;
	GlobalState::fertility = fertility;		
	GlobalState::bacteriaType = tempType; 
	SetOptimalTemperature();
	for (size_t i = 0; i < startingPopulation; i++) 
	{
		initialPopulation.emplace_back();
		initialPopulation[i].SetIsMature(false);
	}
}
void TempCheckMaturity()
{
	for (int i = 0; i < GlobalState::initialPopulation.size(); i++)
	{
		if (GlobalState::initialPopulation[i].GetIsMature() && !GlobalState::initialPopulation[i].bWascounted)
		{
			GlobalState::maturedPopulation++;
			GlobalState::initialPopulation[i].bWascounted = true;
		}
	}
}


void GlobalState::Update()
{ 

	if ((int)livingPopulation.size() > 0)
	{
		ConsoleHelper();
	}
	if ((int)livingPopulation.size() == 0 && TimerManager::elapsedTime > LAG_TIMER + 5)
	{
		printf("Ending simulation...\n");
		EndSimulation();
		return;
	}
	ManageStates(); 
	TempCheckMaturity();     
}

void GlobalState::ManageEnergy()  
{
	if (livingPopulation.size() <= 0)return;
	if (GlobalState::food <= 0)return;  
	for (auto& entity : livingPopulation)
	{
		if (GlobalState::food <= 0)return;
		if (entity.GetEnergy() >= 100)
		{
			ManageDivision(entity);
			continue; 
		}
		entity.SetEnergy(entity.GetEnergy() + GROWTH_RATE);   
		if ((GlobalState::food - requiredEnergy) <= 0)
		{
			return;
		}
		GlobalState::food -= requiredEnergy; 
	}
}

void GlobalState::ManageHealth()
{
	if (livingPopulation.size() <= 0)return;
	uint32_t  count = 0;    
	for (auto& entity : GlobalState::livingPopulation)
	{
		if (entity.GetEnergy() <= 0) 
		{
			entity.SetHealth(entity.GetHealth() - 10);   
		}
		else 
		{
			ManageDecay(entity);  
		}
		if (entity.GetHealth() <= 0)
		{
			ManageDeath(count);   
			count--;
		}
		count++;  
	}
}

void GlobalState::ManageGraduation()
{
	if (TimerManager::elapsedTime < LAG_TIMER || TimerManager::elapsedTime > 50)
		return;
	for (int i = 0; i < initialPopulation.size(); i++)
	{
		if (initialPopulation[i].GetIsMature())
		{
			livingPopulation.push_back(std::move(initialPopulation[i]));
			initialPopulation.erase(initialPopulation.begin() + i); 
			i--;
		}
	}
}

void GlobalState::ManageDeath(const uint32_t index)
{
	if (GlobalState::livingPopulation.size() <= 0)return; 
	livingPopulation.erase(GlobalState::livingPopulation.begin() + index);
}

void GlobalState::ManageDecay(Entity& entity)
{
	entity.SetEnergy(entity.GetEnergy() - 5); 
}

void GlobalState::ManageStates()
{ 
	GrowFood();
	ManageGraduation();
	CalculateNeededEnergy();    
	ManageEnergy();
	ManageHealth();
}

void GlobalState::ManageDivision(Entity& entity) 
{
	entity.SetDefaults();
	GlobalState::livingPopulation.emplace_back();   
}

int GlobalState::GetPrematureDeaths()
{
	if (TimerManager::elapsedTime < LAG_TIMER)
	{
		return 0;
	}
	else
	{
		return  STARTING_POPULATION - GlobalState::maturedPopulation; 
	}
	return 0;
}

void GlobalState::WipePopulation()
{
	if (GlobalState::initialPopulation.size() > 0)
	{
		//for (int i = 0; i < GlobalState::initialPopulation.size(); i++)
		//{
			GlobalState::initialPopulation.clear(); 
		//}
	}
	//for (int i = 0; i < GlobalState::livingPopulation.size(); i++)
	//{
	GlobalState::livingPopulation.clear();  
	//}
}

void GlobalState::GrowFood()
{
	GlobalState::food += FOOD_GROWTH;     
}

void GlobalState::EndSimulation()
{
	printf("Society has collapsed. Nothing to Update\n");
}

void GlobalState::CalculateNeededEnergy()
{
	int difference = abs(optimalTemperature - GlobalState::temperature);//calculate difference 
	//if difference is too big kill all population {}
	if (difference > CRITICAL_TEMPERATURE_DIF) 
	{
		WipePopulation();
	}
	requiredEnergy = 0;
	for (int i = 0; i < difference; i+=5)
	{
		//for every 5 units away from optimal temp add 1 to the required energy to stay alive
		requiredEnergy++;
	}
	//if temp is already in optimal range make sure its set to default 1
	if (requiredEnergy == 0)
	{
		requiredEnergy = 1;
	}
}

void GlobalState::ConsoleHelper()
{
	//printf("Population: %d\n", GlobalState::GetPopulation());
	//printf("Global food: %d\n", GlobalState::food);
	//printf("Called to update the state of the Universe\n\n");
}

void GlobalState::SetOptimalTemperature()
{
	switch (bacteriaType)
	{
	case BacteriaTempType::PSYCHROPHILES: 
		optimalTemperature = 12;
		break; 
	case BacteriaTempType::MESOPHILES: 
		optimalTemperature = 35;
		break;
	case BacteriaTempType::THERMOPHILES: 
		optimalTemperature = 65;
		break;
	case BacteriaTempType::HYPERTHERMOPHILES: 
		optimalTemperature = 95;
		break;
	default:
		break;
	}
}

int GlobalState::GetPopulation() 
{
	return (uint32_t)GlobalState::livingPopulation.size() + (uint32_t)GlobalState::initialPopulation.size();    
}
