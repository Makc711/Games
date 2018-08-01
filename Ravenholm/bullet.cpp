/////////////////////////////////////
// Подключаемые библиотеки
#include "bullet.h"
#include "gameObject.h"
#include "level.h"
#include "items.h"


extern GameObject objects[];
extern GLuint textureItems[];


/////////////////////////////////////
// Функции
void createBullet(int indexOfObject)
{
	createGameObject(indexOfObject);

	objects[indexOfObject].type = GameObjectType_Bullet;
	objects[indexOfObject].layer = GameObjectLayerType_Units;
	objects[indexOfObject].ownerType = GameObjectType_None;
	objects[indexOfObject].width = kBulletDiameterPixels;
	objects[indexOfObject].height = kBulletDiameterPixels;
	objects[indexOfObject].spriteWidth = kBulletDiameterPixels;
	objects[indexOfObject].spriteHeight = kBulletDiameterPixels;
	objects[indexOfObject].sprite = textureItems[ItemType_Bullet];
}

void bulletIntersect(int indexOfBullet, int indexOfTargetObject)
{
	// Уничтожить себя
	objects[indexOfBullet].health = 0;

	// Нанести урон цели
	gameObjectDoDamage(kDamageFromPistolBullet, indexOfTargetObject);
}