#pragma once
#include <cstdint>

class Entity
{
public:
	float maturityDelay;

	//temporary for debug
	bool bWascounted;
private:
	uint8_t health;
	uint8_t energy;
	uint8_t maxHealth;  
	bool bIsMature; 
public:
	Entity()
	{
		SetDefaults(); 
	};
	int GetHealth();
	void SetHealth(uint8_t value); 
	int GetEnergy();
	void SetEnergy(uint8_t value);   
	void SetDefaults();     
	bool GetIsMature();
	void SetIsMature(bool bValue); 
};