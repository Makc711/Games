/////////////////////////////////////
// Подключаемые библиотеки
#include "unitsActions.h"
#include "gameObject.h"
#include "game.h"
#include "level.h"
#include <stdlib.h>


/////////////////////////////////////
// Глобальные переменные
extern GameObject objects[];


/////////////////////////////////////
// Прототипы функций
static void calculateFrontCellPosition(float *x, float *y, int indexOfObject);
static int checkIntersectsInFrontOfTheObject(float frontX, float frontY, int indexOfObject);


/////////////////////////////////////
// Функции
void update(float dt, int indexOfObject, float unitTurnSpeed)
{
	gameObjectUpdate(dt, indexOfObject);

	if (objects[indexOfObject].scratchingTime > 0)
		objects[indexOfObject].scratchingTime -= dt;
	if (objects[indexOfObject].fireCooldownTime > 0)
		objects[indexOfObject].fireCooldownTime -= dt;

	double unitDirectionAngle = objects[indexOfObject].directionAngle;
	float turningAngle = dt * unitTurnSpeed;
	switch (objects[indexOfObject].direction)
	{
		case Direction_Right:
			objects[indexOfObject].directionAngle = calculateDirectionAngle(unitDirectionAngle, turningAngle, 0);
			break;
		case Direction_Up:
			objects[indexOfObject].directionAngle = calculateDirectionAngle(unitDirectionAngle, turningAngle, 90);
			break;
		case Direction_Left:
			objects[indexOfObject].directionAngle = calculateDirectionAngle(unitDirectionAngle, turningAngle, 180);
			break;
		case Direction_Down:
			objects[indexOfObject].directionAngle = calculateDirectionAngle(unitDirectionAngle, turningAngle, 270);
			break;
	}
}

double calculateDirectionAngle(double unitDirectionAngle, float turningAngle, int alpha)
{
	double newUnitDirectionAngle = unitDirectionAngle;
	if (unitDirectionAngle != alpha)
	{
		double directionAngle = 0.0;
		double fourth10 = alpha + turningAngle;
		double fourth11 = alpha + 90;
		double fourth20 = (alpha + 90) % 360;
		double fourth21 = (alpha + 179) % 360 + 0.9999;
		double fourth30 = (alpha + 180) % 360;
		double fourth31 = (alpha + 269) % 360 + 0.9999;
		double fourth40 = (alpha + 270) % 360;
		double fourth41 = (alpha + 360) % 360 - turningAngle;
		if (fourth41 < 0)
		{
			fourth41 += 360;
		}
		if ((unitDirectionAngle >= fourth10 && unitDirectionAngle < fourth11) ||
			(unitDirectionAngle >= fourth20 && unitDirectionAngle <= fourth21))
		{
			directionAngle = unitDirectionAngle - turningAngle;
		}
		else if ((unitDirectionAngle >= fourth30 && unitDirectionAngle <= fourth31) ||
				 (unitDirectionAngle >= fourth40 && unitDirectionAngle <= fourth41))
		{
			directionAngle = unitDirectionAngle + turningAngle;
		}
		else
		{
			directionAngle = alpha;
		}

		if (directionAngle < 0)
		{
			directionAngle += 360;
		}
		else if (directionAngle > 360)
		{
			directionAngle -= 360;
		}

		newUnitDirectionAngle = directionAngle;
	}
	return newUnitDirectionAngle;
}

void move(Direction direction, int indexOfObject)
{
	objects[indexOfObject].direction = direction;

	objects[indexOfObject].xSpeed = 0.0f;
	objects[indexOfObject].ySpeed = 0.0f;

	switch (direction)
	{
		case Direction_Left:  objects[indexOfObject].xSpeed = -objects[indexOfObject].speed; break;
		case Direction_Right: objects[indexOfObject].xSpeed =  objects[indexOfObject].speed; break;
		case Direction_Up:    objects[indexOfObject].ySpeed = -objects[indexOfObject].speed; break;
		case Direction_Down:  objects[indexOfObject].ySpeed =  objects[indexOfObject].speed; break;
	}
}

int findDistanceToObject(float *distance, int indexOfObject)
{
	float x = 0.0f;
	float y = 0.0f;
	calculateFrontCellPosition(&x, &y, indexOfObject);

	float xDelta = 0.0f;
	float yDelta = 0.0f;

	switch (objects[indexOfObject].direction)
	{ // Увеличиваем по 1 пикселю и анализируем расстояние до цели
		case Direction_Left:  xDelta = -1.0f; break;
		case Direction_Right: xDelta =  1.0f; break;
		case Direction_Up:    yDelta = -1.0f; break;
		case Direction_Down:  yDelta =  1.0f; break;
	}

	int indexOfTargetObject = -1;
	float distanceToObject = 0;
	do
	{
		indexOfTargetObject = checkIntersectsInFrontOfTheObject(x, y, indexOfObject);

		x += xDelta;
		y += yDelta;
		++distanceToObject;
	} while (indexOfTargetObject == -1);

	(*distance) = distanceToObject;
	return indexOfTargetObject;
}

static int checkIntersectsInFrontOfTheObject(float frontX, float frontY, int indexOfObject)
{
	int x00 = int(frontX); 
	int y00 = int(frontY);
	int x01 = int(frontX);
	int y01 = int(frontY);

	switch (objects[indexOfObject].direction)
	{
		case Direction_Left:
		case Direction_Right:
			x00 = int(frontX);
			y00 = int(frontY - float(objects[indexOfObject].height) / 2.0f);
			x01 = x00;
			y01 = y00 + objects[indexOfObject].height - 1;
			break;

		case Direction_Up:
		case Direction_Down:
			x00 = int(frontX - float(objects[indexOfObject].width) / 2.0f);
			y00 = int(frontY);
			x01 = x00 + objects[indexOfObject].width - 1;
			y01 = y00;
			break;
	}

	for (int i = 0; i < kObjectsCountMax; i++)
	{
		if (objects[i].isObjectBusy && objects[i].physical && i != indexOfObject)
		{
			int x10 = int(objects[i].x);
			int y10 = int(objects[i].y);
			int x11 = x10 + objects[i].width - 1;
			int y11 = y10 + objects[i].height - 1;

			if (x00 <= x11 && x01 >= x10 && y00 <= y11 && y01 >= y10)
				return i;
		}
	}
	return -1;
}

void scratch(int indexOfObject, int indexOfTargetObject, int damage, float recoveryTime)
{
	if (objects[indexOfObject].scratchingTime > 0)
		return;

	objects[indexOfObject].scratchingTime = recoveryTime;

	gameObjectDoDamage(damage, indexOfTargetObject);
}

bool fire(int indexOfObject)
{
	if (objects[indexOfObject].fireCooldownTime > 0)
		return false;

	objects[indexOfObject].fireCooldownTime = kMilitaryFireCooldownTime;

	float x = 0.0f;
	float y = 0.0f;
	float xSpeed = 0.0f;
	float ySpeed = 0.0f;

	calculateFrontCellPosition(&x, &y, indexOfObject);

	switch (objects[indexOfObject].direction)
	{
		case Direction_Left:
			x = x - kBulletDiameterPixels;
			y = y - float(kBulletDiameterPixels) / 2.0f;
			xSpeed = -kPistolBulletSpeed; 
			break;

		case Direction_Right:
			y = y - float(kBulletDiameterPixels) / 2.0f;
			xSpeed = kPistolBulletSpeed; 
			break;

		case Direction_Up:
			y = y - kBulletDiameterPixels;
			x = x - float(kBulletDiameterPixels) / 2.0f;
			ySpeed = -kPistolBulletSpeed;
			break;

		case Direction_Down:
			x = x - float(kBulletDiameterPixels) / 2.0f;
			ySpeed = kPistolBulletSpeed;
			break;
	}

	int indexOfCreatedObject = createObject(GameObjectType_Bullet, x, y, 0.0, 0);
	if (indexOfCreatedObject != -1)
	{
		objects[indexOfCreatedObject].ownerType = objects[indexOfObject].type;
		objects[indexOfCreatedObject].xSpeed = xSpeed;
		objects[indexOfCreatedObject].ySpeed = ySpeed;
	}
	return true;
}

static void calculateFrontCellPosition(float *x, float *y, int indexOfObject)
{
	switch (objects[indexOfObject].direction)
	{
		case Direction_Left:
			(*x) = float(int(objects[indexOfObject].x));
			(*y) = int(objects[indexOfObject].y) + (float(objects[indexOfObject].height) / 2.0f);
			break;

		case Direction_Right:
			(*x) = float(int(objects[indexOfObject].x) + objects[indexOfObject].width);
			(*y) = int(objects[indexOfObject].y) + (float(objects[indexOfObject].height) / 2.0f);
			break;

		case Direction_Up:
			(*y) = float(int(objects[indexOfObject].y));
			(*x) = int(objects[indexOfObject].x) + (float(objects[indexOfObject].width) / 2.0f);
			break;

		case Direction_Down:
			(*y) = float(int(objects[indexOfObject].y) + objects[indexOfObject].height);
			(*x) = int(objects[indexOfObject].x) + (float(objects[indexOfObject].width) / 2.0f);
			break;
	}
}

void moveRandomDirection(int indexOfObject)
{
	Direction prevDirection = objects[indexOfObject].direction;
	Direction newDirection;
	do
	{
		newDirection = Direction(rand() % Direction_MAX);
	} while (prevDirection == newDirection);

	move(newDirection, indexOfObject);
}

void changeAction(int indexOfObject, int action)
{
	if (objects[indexOfObject].action != action)
	{
		objects[indexOfObject].action = action;
		objects[indexOfObject].currentFrame = 0.0f;
	}
}

void changeFrame(float dt, int indexOfObject, int idleAction, GLuint *texture, const int numberOfFrames, const int animationSpeed)
{
	if (objects[indexOfObject].currentFrame >= 0 && objects[indexOfObject].currentFrame < numberOfFrames)
	{
		objects[indexOfObject].sprite = texture[int(objects[indexOfObject].currentFrame)];
		objects[indexOfObject].currentFrame += dt * animationSpeed;
	}
	else
	{
		objects[indexOfObject].currentFrame = 0.0f;
		objects[indexOfObject].sprite = texture[int(objects[indexOfObject].currentFrame)];
		objects[indexOfObject].action = idleAction;
	}
}

void setUnitSpriteWidth(int indexOfObject, const int spriteWidthPixels, const int spriteSize)
{
	objects[indexOfObject].spriteWidth = spriteWidthPixels * kPixelsPerCell / spriteSize;
}

void setUnitSpriteHeight(int indexOfObject, const int spriteHeightPixels, const int spriteSize)
{
	objects[indexOfObject].spriteHeight = spriteHeightPixels * kPixelsPerCell / spriteSize;
}