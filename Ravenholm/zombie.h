#pragma once

enum ZombieActions
{
	Zombie_Idle,
	Zombie_Walk,
	Zombie_Attac0,
	Zombie_Attac1,
	Zombie_Attac2,
	Zombie_Attac3
};


struct Zombie
{
	float analizeTimer;
	float analizeTime;

	float lastAnalizeX;
	float lastAnalizeY;
};


/////////////////////////////////////
// Прототипы функций
void createZombie(int indexOfObject);
void zombieUpdate(float dt, int indexOfObject);
void zombieRender(float dt, int indexOfObject);