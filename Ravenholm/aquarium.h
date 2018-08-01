#pragma once

enum AquariumActions
{
	Aquarium_Idle,
	Aquarium_Break
};


/////////////////////////////////////
// Прототипы функций
void createAquarium(int indexOfObject);
void aquariumUpdate(float dt, int indexOfObject);
void aquariumRender(float dt, int indexOfObject);