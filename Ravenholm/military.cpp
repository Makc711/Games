/////////////////////////////////////
// Подключаемые библиотеки
#include "military.h"
#include "level.h"
#include "gameObject.h"
#include "utils.h"
#include "unitsActions.h"
#include "textures.h"


Military military;
extern GameObject objects[];
extern GLuint textureMilitaryAK47Idle[];
extern GLuint textureMilitaryAK47RunningWithAiming[];
extern GLuint textureMilitaryAK47Shoot[];
extern GLuint textureMilitaryAK47Knife[];
extern GLuint textureMilitaryAK47SmallDamage[];
extern GLuint textureMilitaryAK47BigDamage[];
extern GLuint textureMilitaryAK47Death[];
extern GLuint textureItems[];


static void setMilitarySpriteSize(int indexOfObject);
static void drawMilitaryData(int indexOfObject);
static void controlOfMilitary(int indexOfObject);


/////////////////////////////////////
// Функции
void createMilitary(int indexOfObject)
{
	createGameObject(indexOfObject);

	objects[indexOfObject].type = GameObjectType_Military;
	objects[indexOfObject].layer = GameObjectLayerType_Military;
	objects[indexOfObject].action = Military_Idle;
	militaryRender(0, indexOfObject);
	objects[indexOfObject].health = kMilitaryHealth;
	objects[indexOfObject].speed = kMilitarySpeed;
	objects[indexOfObject].width = kMilitaryPixelsSize;
	objects[indexOfObject].height = kMilitaryPixelsSize;
	setMilitarySpriteSize(indexOfObject);
	objects[indexOfObject].destroyAfterDeath = false;

	military.keyLeft = 0;
	military.keyRight = 0;
	military.keyUp = 0;
	military.keyDown = 0;
	military.keyFire = 0;
	military.keyScratch = 0;
	military.ammunition = kMilitaryAmmunition;
	military.lastHealth = objects[indexOfObject].health;
}

void militarySetKeys(int keyLeft, int keyRight, int keyUp, int keyDown, int keyFire, int keyScratch)
{
	military.keyLeft = keyLeft;
	military.keyRight = keyRight;
	military.keyUp = keyUp;
	military.keyDown = keyDown;
	military.keyFire = keyFire;
	military.keyScratch = keyScratch;
}

static void setMilitarySpriteSize(int indexOfObject)
{
	switch (objects[indexOfObject].action)
	{
		case Military_Idle:
			setUnitSpriteWidth(indexOfObject, kMilitaryAK47IdleWidth, kMilitarySpriteSize);
			setUnitSpriteHeight(indexOfObject, kMilitaryAK47IdleHeight, kMilitarySpriteSize);
			break;
		case Military_Run:
			setUnitSpriteWidth(indexOfObject, kMilitaryAK47RunningWithAimingWidth, kMilitarySpriteSize);
			setUnitSpriteHeight(indexOfObject, kMilitaryAK47RunningWithAimingHeight, kMilitarySpriteSize);
			break;
		case Military_Shoot:
			setUnitSpriteWidth(indexOfObject, kMilitaryAK47ShootWidth, kMilitarySpriteSize);
			setUnitSpriteHeight(indexOfObject, kMilitaryAK47ShootHeight, kMilitarySpriteSize);
			break;
		case Military_Knife:
			setUnitSpriteWidth(indexOfObject, kMilitaryAK47KnifeWidth, kMilitarySpriteSize);
			setUnitSpriteHeight(indexOfObject, kMilitaryAK47KnifeHeight, kMilitarySpriteSize);
			break;
		case Military_LiteDamage:
			setUnitSpriteWidth(indexOfObject, kMilitaryAK47SmallDamageWidth, kMilitarySpriteSize);
			setUnitSpriteHeight(indexOfObject, kMilitaryAK47SmallDamageHeight, kMilitarySpriteSize);
			break;
		case Military_HardDamage:
			setUnitSpriteWidth(indexOfObject, kMilitaryAK47BigDamageWidth, kMilitarySpriteSize);
			setUnitSpriteHeight(indexOfObject, kMilitaryAK47BigDamageHeight, kMilitarySpriteSize);
			break;
		case Military_Death:
			setUnitSpriteWidth(indexOfObject, kMilitaryAK47DeathWidth, kMilitarySpriteSize);
			setUnitSpriteHeight(indexOfObject, kMilitaryAK47DeathHeight, kMilitarySpriteSize);
			break;
	}
}

void militaryRender(float dt, int indexOfObject)
{
	switch (objects[indexOfObject].action)
	{
		case Military_Idle:
			changeFrame(dt, indexOfObject, Military_Idle, textureMilitaryAK47Idle, kNumberOfFramesMilitaryAK47Idle, kMilitaryAK47IdleAnimationSpeed);
			break;
		case Military_Run:
			changeFrame(dt, indexOfObject, Military_Idle, textureMilitaryAK47RunningWithAiming, kNumberOfFramesMilitaryAK47RunningWithAiming, kMilitaryAK47RunningWithAimingAnimationSpeed);
			break;
		case Military_Shoot:
			changeFrame(dt, indexOfObject, Military_Idle, textureMilitaryAK47Shoot, kNumberOfFramesMilitaryAK47Shoot, kMilitaryAK47ShootAnimationSpeed);
			break;
		case Military_Knife:
			changeFrame(dt, indexOfObject, Military_Idle, textureMilitaryAK47Knife, kNumberOfFramesMilitaryAK47Knife, kMilitaryAK47KnifeAnimationSpeed);
			break;
		case Military_LiteDamage:
			changeFrame(dt, indexOfObject, Military_Idle, textureMilitaryAK47SmallDamage, kNumberOfFramesMilitaryAK47SmallDamage, kMilitaryAK47SmallDamageAnimationSpeed);
			break;
		case Military_HardDamage:
			changeFrame(dt, indexOfObject, Military_Idle, textureMilitaryAK47BigDamage, kNumberOfFramesMilitaryAK47BigDamage, kMilitaryAK47BigDamageAnimationSpeed);
			break;
		case Military_Death:
			if (objects[indexOfObject].currentFrame >= 0 && objects[indexOfObject].currentFrame < kNumberOfFramesMilitaryAK47Death)
			{
				objects[indexOfObject].sprite = textureMilitaryAK47Death[int(objects[indexOfObject].currentFrame)];
				objects[indexOfObject].currentFrame += dt * kMilitaryAK47DeathAnimationSpeed;
			}
			break;
	}
	drawMilitaryData(indexOfObject);
}

static void drawMilitaryData(int indexOfObject)
{
	for (int i = 0; i < kMilitaryHealth; i++)
	{
		ItemsType type;
		if (objects[indexOfObject].health - i > 0)
		{
			type = ItemType_Health;
		}
		else
		{
			type = ItemType_NoHealth;
		}
		drawTexture(kHealthLeftDistance + i * (kHealthWidthPixels + kPixelsBetweenHealth), kHealthTopDistance, kHealthWidthPixels, kHealthHeightPixels, textureItems[type], false);
	}
	for (int i = 0; i < kMilitaryAmmunition; i++)
	{
		ItemsType type;
		if (military.ammunition - i > 0)
		{
			type = ItemType_Ammunition;
		}
		else
		{
			type = ItemType_NoAmmunition;
		}
		drawTexture(kAmmunitionLeftDistance + i * (kAmmunitionWidthPixels + kPixelsBetweenAmmunition), kAmmunitionTopDistance, kAmmunitionWidthPixels, kAmmunitionHeightPixels, textureItems[type], false);
	}
}

void militaryUpdate(float dt, int indexOfObject)
{
	update(dt, indexOfObject, kMilitaryTurnSpeed);

	if (objects[indexOfObject].action == Military_Idle ||
		objects[indexOfObject].action == Military_Run)
	{
		if (objects[indexOfObject].xSpeed != 0 ||
			objects[indexOfObject].ySpeed != 0)
		{
			changeAction(indexOfObject, Military_Run);
		}
		else
		{
			changeAction(indexOfObject, Military_Idle);
		}
	}

	if (objects[indexOfObject].health <= 0)
	{
		objects[indexOfObject].xSpeed = 0.0f;
		objects[indexOfObject].ySpeed = 0.0f;
		objects[indexOfObject].physical = false;
		changeAction(indexOfObject, Military_Death);
	}
	else
	{
		if (military.lastHealth - objects[indexOfObject].health > 0)
		{
			if (military.lastHealth - objects[indexOfObject].health < kHardDamage)
			{
				changeAction(indexOfObject, Military_LiteDamage);
			}
			else
			{
				changeAction(indexOfObject, Military_HardDamage);
			}
			military.lastHealth = objects[indexOfObject].health;
			objects[indexOfObject].xSpeed = 0.0f;
			objects[indexOfObject].ySpeed = 0.0f;
		}
	}

	if (objects[indexOfObject].health > 0 &&
		(objects[indexOfObject].action == Military_Idle || objects[indexOfObject].action == Military_Run))
	{
		controlOfMilitary(indexOfObject);
	}

	setMilitarySpriteSize(indexOfObject);
}

static void controlOfMilitary(int indexOfObject)
{
	if (isKeyDown(military.keyLeft))
		move(Direction_Left, indexOfObject);
	else
		if (isKeyDown(military.keyRight))
			move(Direction_Right, indexOfObject);
		else
			if (isKeyDown(military.keyUp))
				move(Direction_Up, indexOfObject);
			else
				if (isKeyDown(military.keyDown))
					move(Direction_Down, indexOfObject);
				else
				{
					objects[indexOfObject].xSpeed = 0.0f;
					objects[indexOfObject].ySpeed = 0.0f;
				}

	if (isKeyDown(military.keyFire))
	{
		if (military.ammunition > 0)
		{
			objects[indexOfObject].xSpeed = 0.0f;
			objects[indexOfObject].ySpeed = 0.0f;
			changeAction(indexOfObject, Military_Shoot);

			if (fire(indexOfObject))
			{
				military.ammunition--;
			}
		}
	}
	else if (isKeyDown(military.keyScratch))
	{
		float distance = 0;
		int indexOfTargetObject = findDistanceToObject(&distance, indexOfObject);

		objects[indexOfObject].xSpeed = 0.0f;
		objects[indexOfObject].ySpeed = 0.0f;
		changeAction(indexOfObject, Military_Knife);

		if (distance <= kMilitaryScratchingDistance)
		{
			scratch(indexOfObject, indexOfTargetObject, kDamageFromMilitaryScratch, kMilitaryScratchingTime);
		}
	}
}