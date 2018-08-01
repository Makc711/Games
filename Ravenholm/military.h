#pragma once

enum MilitaryActions
{
	Military_Idle,
	Military_Run,
	Military_Shoot,
	Military_Knife,
	Military_LiteDamage,
	Military_HardDamage,
	Military_Death
};


struct Military
{
	int keyLeft;
	int keyRight;
	int keyUp;
	int keyDown;
	int keyFire;
	int keyScratch;
	int ammunition;
	int lastHealth;
};


/////////////////////////////////////
// Прототипы функций
void createMilitary(int indexOfObject);
void militarySetKeys(int keyLeft, int keyRight, int keyUp, int keyDown, int keyFire, int keyScratch);
void militaryUpdate(float dt, int indexOfObject);
void militaryRender(float dt, int indexOfObject);