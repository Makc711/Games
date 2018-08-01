/////////////////////////////////////
// Подключаемые библиотеки
#include "gameOver.h"
#include "gameObject.h"
#include "game.h"
#include "textures.h"
#include "level.h"


extern GameObject objects[];
extern GLuint textureYouAreDied;


/////////////////////////////////////
// Функции
void createGameOverLable()
{
	for (int i = 0; i < kObjectsCountMax; i++)
	{
		if (objects[i].isObjectBusy == false)
		{
			createGameObject(i);
			objects[i].type = GameObjectType_GameOver;
			objects[i].layer = GameObjectLayerType_GameOver;
			objects[i].sprite = textureYouAreDied;
			objects[i].x = kScreenWidth / 2;
			objects[i].y = kScreenHeight / 2;
			objects[i].spriteWidth = int(kTextureYouAreDiedWidthCells * kPixelsPerCell);
			objects[i].spriteHeight = int(kTextureYouAreDiedHeightCells * kPixelsPerCell);
			objects[i].directionAngle = 10.0;
			objects[i].physical = false;
			objects[i].isObjectBusy = true;
			objects[i].isObjectVisible = false;
			return;
		}
	}
}

void updateGameOverLable(float dt, int indexOfObject)
{
	gameObjectUpdate(dt, indexOfObject);

	if (objects[indexOfObject].currentFrame >= 0 && objects[indexOfObject].currentFrame <= kNumberOfFramesYouAreDied && objects[indexOfObject].isObjectVisible)
	{
		objects[indexOfObject].spriteWidth = int(kTextureYouAreDiedWidthCells * kPixelsPerCell * objects[indexOfObject].currentFrame / kNumberOfFramesYouAreDied);
		objects[indexOfObject].spriteHeight = int(kTextureYouAreDiedHeightCells * kPixelsPerCell * objects[indexOfObject].currentFrame / kNumberOfFramesYouAreDied);
		objects[indexOfObject].currentFrame += dt * kYouAreDiedAnimationSpeed;
	}
}