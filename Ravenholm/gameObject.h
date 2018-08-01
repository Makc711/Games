#pragma once

/////////////////////////////////////
// Подключаемые библиотеки
#include "gameObjectType.h"
#include "glfw3.h"
#include "direction.h"


struct GameObject
{
	GameObjectType type;
	GameObjectLayerType layer;
	int action;

	float x; // Координаты верхнего левого угла объекта (пикселей)
	float y;
	float spriteX; // Координаты верхнего левого угла спрайта (пикселей)
	float spriteY;
	float xSpeed;
	float ySpeed;

	float speed;

	int width; // Ширина и высота объекта (пикселей)
	int height;
	int spriteWidth; // Ширина и высота спрайта
	int spriteHeight;
	float currentFrame;

	int health;
	bool destroyAfterDeath;
	bool invulnerable;

	bool physical;
	float scratchingTime;
	float fireCooldownTime;

	Direction direction;
	double directionAngle;
	GameObjectType ownerType; // Тип объекта, создавшего снаряд

	GLuint sprite;

	bool isObjectBusy;
	bool isObjectVisible;
};


/////////////////////////////////////
// Прототипы функций
void createGameObject(int indexOfObject);
void gameObjectRender(float dt, int indexOfObject);
void gameObjectUpdate(float dt, int indexOfObject);
float gameObjectSpriteX(int indexOfObject);
float gameObjectSpriteY(int indexOfObject);
void gameObjectIntersect(int indexOfObject, int indexOfOtherObject);
void gameObjectDoDamage(int damage, int indexOfObject);