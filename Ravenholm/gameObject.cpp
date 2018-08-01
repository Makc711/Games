/////////////////////////////////////
// Подключаемые библиотеки
#include "gameObject.h"
#include "openglLib.h"
#include "game.h"
#include "bullet.h"
#include "military.h"
#include "zombie.h"
#include "level.h"
#include "aquarium.h"


/////////////////////////////////////
// Глобальные переменные
extern GameObject objects[];


/////////////////////////////////////
// Функции
void createGameObject(int indexOfObject)
{
	objects[indexOfObject].type = GameObjectType_None;
	objects[indexOfObject].layer = GameObjectLayerType_Background;
	objects[indexOfObject].action = 0;

	objects[indexOfObject].x = 0.0f;
	objects[indexOfObject].y = 0.0f;
	objects[indexOfObject].spriteX = gameObjectSpriteX(indexOfObject);
	objects[indexOfObject].spriteY = gameObjectSpriteY(indexOfObject);
	objects[indexOfObject].xSpeed = 0.0f;
	objects[indexOfObject].ySpeed = 0.0f;

	objects[indexOfObject].speed = 0.0f;

	objects[indexOfObject].width = kPixelsPerCell;
	objects[indexOfObject].height = kPixelsPerCell;
	objects[indexOfObject].spriteWidth = kPixelsPerCell;
	objects[indexOfObject].spriteHeight = kPixelsPerCell;
	objects[indexOfObject].currentFrame = 0.0f;

	objects[indexOfObject].health = 1;
	objects[indexOfObject].destroyAfterDeath = true;
	objects[indexOfObject].invulnerable = false;

	objects[indexOfObject].physical = true;
	objects[indexOfObject].scratchingTime = 0.0f;
	objects[indexOfObject].fireCooldownTime = 0.0f;

	objects[indexOfObject].direction = Direction_Right;
	objects[indexOfObject].directionAngle = 0.0;
	objects[indexOfObject].ownerType = GameObjectType_None;

	objects[indexOfObject].sprite = 0;
}


void gameObjectRender(float dt, int indexOfObject)
{ // Меняем спрайты для анимации объектов
	switch (objects[indexOfObject].type)
	{
		case GameObjectType_Aquarium:
			aquariumRender(dt, indexOfObject);
			break;

		case GameObjectType_Military:
			militaryRender(dt, indexOfObject);
			break;

		case GameObjectType_Zombie:
			zombieRender(dt, indexOfObject);
			break;
	}

	if (objects[indexOfObject].type != GameObjectType_None)
	{
		drawRotateTexture(int(objects[indexOfObject].spriteX), int(objects[indexOfObject].spriteY), objects[indexOfObject].spriteWidth, objects[indexOfObject].spriteHeight, objects[indexOfObject].sprite, objects[indexOfObject].directionAngle);
	}
}

void gameObjectUpdate(float dt, int indexOfObject)
{
	int oldIntX = int(objects[indexOfObject].x);
	int oldIntY = int(objects[indexOfObject].y);

	float newX = objects[indexOfObject].x + objects[indexOfObject].xSpeed * dt;
	float newY = objects[indexOfObject].y + objects[indexOfObject].ySpeed * dt;

	int newIntX = int(newX);
	int newIntY = int(newY);

	if (oldIntX != newIntX)
		moveObjectTo(indexOfObject, newX, objects[indexOfObject].y);
	else
	{
		objects[indexOfObject].x = newX;
		objects[indexOfObject].spriteX = gameObjectSpriteX(indexOfObject);
	}
		

	if (oldIntY != newIntY)
		moveObjectTo(indexOfObject, objects[indexOfObject].x, newY);
	else
	{
		objects[indexOfObject].y = newY;
		objects[indexOfObject].spriteY = gameObjectSpriteY(indexOfObject);
	}
}

float gameObjectSpriteX(int indexOfObject)
{
	return objects[indexOfObject].x + objects[indexOfObject].width / 2 - objects[indexOfObject].spriteWidth / 2;
}

float gameObjectSpriteY(int indexOfObject)
{
	return objects[indexOfObject].y + objects[indexOfObject].height / 2 - objects[indexOfObject].spriteHeight / 2;
}

void gameObjectIntersect(int indexOfObject, int indexOfOtherObject)
{
	switch (objects[indexOfObject].type)
	{
		case GameObjectType_Bullet:
			bulletIntersect(indexOfObject, indexOfOtherObject);
			break;
	}
}

void gameObjectDoDamage(int damage, int indexOfObject)
{
	if (objects[indexOfObject].invulnerable)
		return;

	if (objects[indexOfObject].health > damage)
		objects[indexOfObject].health -= damage;
	else
		objects[indexOfObject].health = 0;
}