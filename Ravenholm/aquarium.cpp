/////////////////////////////////////
// Подключаемые библиотеки
#include "aquarium.h"
#include "gameObject.h"
#include "level.h"
#include "textures.h"
#include "unitsActions.h"


extern GameObject objects[];
extern GLuint textureAquariumIdle[kNumberOfFramesAquariumIdle];
extern GLuint textureAquariumBreak[kNumberOfFramesAquariumBreak];


/////////////////////////////////////
// Функции
void createAquarium(int indexOfObject)
{
	createGameObject(indexOfObject);

	objects[indexOfObject].type = GameObjectType_Aquarium;
	objects[indexOfObject].layer = GameObjectLayerType_Objects;
	objects[indexOfObject].action = Aquarium_Idle;
	aquariumRender(0, indexOfObject);
	objects[indexOfObject].width = kAquariumWidthPixels;
	objects[indexOfObject].height = kAquariumHeightPixels;
	objects[indexOfObject].spriteWidth = kAquariumSpriteWidthPixels;
	objects[indexOfObject].spriteHeight = kAquariumSpriteHeightPixels;
	objects[indexOfObject].destroyAfterDeath = false;
}

void aquariumRender(float dt, int indexOfObject)
{
	switch (objects[indexOfObject].action)
	{
		case Aquarium_Idle:
			changeFrame(dt, indexOfObject, Aquarium_Idle, textureAquariumIdle, kNumberOfFramesAquariumIdle, kAquariumAnimationSpeed);
			break;

		case Aquarium_Break:
			if (objects[indexOfObject].currentFrame >= 0 && objects[indexOfObject].currentFrame < kNumberOfFramesAquariumBreak)
			{
				objects[indexOfObject].sprite = textureAquariumBreak[int(objects[indexOfObject].currentFrame)];
				objects[indexOfObject].currentFrame += dt * kAquariumAnimationSpeed;
			}
			break;
	}
}

void aquariumUpdate(float dt, int indexOfObject)
{
	gameObjectUpdate(dt, indexOfObject);

	if (objects[indexOfObject].health != 0)
	{
		changeAction(indexOfObject, Aquarium_Idle);
	}
	else
	{
		changeAction(indexOfObject, Aquarium_Break);
	}
}