/////////////////////////////////////
// Подключаемые библиотеки
#include "zombie.h"
#include "level.h"
#include "gameObject.h"
#include "utils.h"
#include "unitsActions.h"
#include <stdlib.h>
#include "textures.h"


Zombie zombie;
extern GameObject objects[];
extern GLuint textureZombieIdle[];
extern GLuint textureZombieWalk[];
extern GLuint textureZombieAttac0[];
extern GLuint textureZombieAttac1[];
extern GLuint textureZombieAttac2[];
extern GLuint textureZombieAttac3[];


/////////////////////////////////////
// Прототипы функций
void zombieAnalize(int indexOfObject);
static void setZombieSpriteSize(int indexOfObject);


/////////////////////////////////////
// Функции
void createZombie(int indexOfObject)
{
	createGameObject(indexOfObject);

	objects[indexOfObject].type = GameObjectType_Zombie;
	objects[indexOfObject].layer = GameObjectLayerType_Units;
	objects[indexOfObject].action = Zombie_Idle;
	zombieRender(0, indexOfObject);
	objects[indexOfObject].health = kZombieHealth;
	objects[indexOfObject].speed = kZombieSpeed;
	objects[indexOfObject].width = kZombiePixelsSize;
	objects[indexOfObject].height = kZombiePixelsSize;
	setZombieSpriteSize(indexOfObject);
	objects[indexOfObject].currentFrame = float(getRandomInt(0, kNumberOfFramesZombieIdle));

	zombie.analizeTime = kZombieAIAnalizeTime;
	zombie.analizeTimer = getRandomFloat(0.0f, zombie.analizeTime);
	zombie.lastAnalizeX = 0.0f;
	zombie.lastAnalizeY = 0.0f;
}

static void setZombieSpriteSize(int indexOfObject)
{
	switch (objects[indexOfObject].action)
	{
		case Zombie_Idle:
			setUnitSpriteWidth(indexOfObject, kZombieIdleWidth, kZombieSpriteSize);
			setUnitSpriteHeight(indexOfObject, kZombieIdleHeight, kZombieSpriteSize);
			break;
		case Zombie_Walk:
			setUnitSpriteWidth(indexOfObject, kZombieWalkWidth, kZombieSpriteSize);
			setUnitSpriteHeight(indexOfObject, kZombieWalkHeight, kZombieSpriteSize);
			break;
		case Zombie_Attac0:
			setUnitSpriteWidth(indexOfObject, kZombieAttac0Width, kZombieSpriteSize);
			setUnitSpriteHeight(indexOfObject, kZombieAttac0Height, kZombieSpriteSize);
			break;
		case Zombie_Attac1:
			setUnitSpriteWidth(indexOfObject, kZombieAttac1Width, kZombieSpriteSize);
			setUnitSpriteHeight(indexOfObject, kZombieAttac1Height, kZombieSpriteSize);
			break;
		case Zombie_Attac2:
			setUnitSpriteWidth(indexOfObject, kZombieAttac2Width, kZombieSpriteSize);
			setUnitSpriteHeight(indexOfObject, kZombieAttac2Height, kZombieSpriteSize);
			break;
		case Zombie_Attac3:
			setUnitSpriteWidth(indexOfObject, kZombieAttac3Width, kZombieSpriteSize);
			setUnitSpriteHeight(indexOfObject, kZombieAttac3Height, kZombieSpriteSize);
			break;
	}
}

void zombieRender(float dt, int indexOfObject)
{
	switch (objects[indexOfObject].action)
	{
		case Zombie_Idle:
			changeFrame(dt, indexOfObject, Zombie_Idle, textureZombieIdle, kNumberOfFramesZombieIdle, kZombieIdleAnimationSpeed);
			break;
		case Zombie_Walk:
			changeFrame(dt, indexOfObject, Zombie_Idle, textureZombieWalk, kNumberOfFramesZombieWalk, kZombieWalkAnimationSpeed);
			break;
		case Zombie_Attac0:
			changeFrame(dt, indexOfObject, Zombie_Idle, textureZombieAttac0, kNumberOfFramesZombieAttac0, kZombieAttac0AnimationSpeed);
			break;
		case Zombie_Attac1:
			changeFrame(dt, indexOfObject, Zombie_Idle, textureZombieAttac1, kNumberOfFramesZombieAttac1, kZombieAttac1AnimationSpeed);
			break;
		case Zombie_Attac2:
			changeFrame(dt, indexOfObject, Zombie_Idle, textureZombieAttac2, kNumberOfFramesZombieAttac2, kZombieAttac2AnimationSpeed);
			break;
		case Zombie_Attac3:
			changeFrame(dt, indexOfObject, Zombie_Idle, textureZombieAttac3, kNumberOfFramesZombieAttac3, kZombieAttac3AnimationSpeed);
			break;
	}
}

void zombieUpdate(float dt, int indexOfObject)
{
	update(dt, indexOfObject, kZombieTurnSpeed);

	if (objects[indexOfObject].action == Zombie_Idle ||
		objects[indexOfObject].action == Zombie_Walk)
	{
		if (objects[indexOfObject].xSpeed != 0.0f ||
			objects[indexOfObject].ySpeed != 0.0f)
		{
			changeAction(indexOfObject, Zombie_Walk);
		}
		else
		{
			changeAction(indexOfObject, Zombie_Idle);
		}
	}

	setZombieSpriteSize(indexOfObject);

	zombie.analizeTimer += dt;
	if (zombie.analizeTimer >= zombie.analizeTime)
	{
		zombie.analizeTimer = 0.0f;
		zombieAnalize(indexOfObject);
	}
}

void zombieAnalize(int indexOfObject)
{
	float distance = 0;
	int indexOfTargetObject = findDistanceToObject(&distance, indexOfObject);

	// Действия атаки
	switch (objects[indexOfTargetObject].type)
	{
		case GameObjectType_Military:
			if (distance <= kZombieScratchingDistance)
			{
				objects[indexOfObject].xSpeed = 0.0f;
				objects[indexOfObject].ySpeed = 0.0f;
				changeAction(indexOfObject, getRandomInt(Zombie_Attac0, Zombie_Attac3));
				scratch(indexOfObject, indexOfTargetObject, kDamageFromZombieScratch, kZombieScratchingTime);
			}
			else
			{
				move(objects[indexOfObject].direction, indexOfObject);
			}
			return;
	}

	// Вероятность 20% смены направления (1/5)
	if (rand() % 5 == 0)
	{
		moveRandomDirection(indexOfObject);
		return;
	}

	// Дополнительное условие смены направления
	if (distance <= kPixelsPerCell * 2
		|| ((int)zombie.lastAnalizeX == (int)objects[indexOfTargetObject].x && (int)zombie.lastAnalizeY == (int)objects[indexOfTargetObject].y))
	{
		moveRandomDirection(indexOfObject);
		return;
	}

	zombie.lastAnalizeX = objects[indexOfTargetObject].x;
	zombie.lastAnalizeY = objects[indexOfTargetObject].y;
}