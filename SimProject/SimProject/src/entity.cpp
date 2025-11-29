#include <includes/entity.h>
#include <libs/sdl/include/SDL3/SDL.h>
#include <includes/timer_manager.h>
int Entity::GetHealth()
{
	return health;
}

void Entity::SetHealth(uint8_t value)   
{
	if (!bIsMature)return;
	health = value;
}

int Entity::GetEnergy()  
{
	return energy; 
}

void Entity::SetEnergy(uint8_t value)   
{
	if (!bIsMature)return; 
	energy = value; 
}

void Entity::SetDefaults()     
{
	//pick two numbers between -10-10
	bWascounted = false;
	health = 100;
	maxHealth = 100;
	energy = 0;
}

bool Entity::GetIsMature()
{
	if (TimerManager::elapsedTime >= maturityDelay)
	{
		bIsMature = true;
	}
	else
	{
		bIsMature = false;
	}
	return bIsMature;
}

 
void Entity::SetIsMature(bool bValue)     
{
	bIsMature = bValue;    
	if (bIsMature)return;
	int rand = SDL_rand(20) + SDL_rand(10) ;
	maturityDelay = rand + TimerManager::elapsedTime;   
}
