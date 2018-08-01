#pragma once

/////////////////////////////////////
// ������������ ����������
#include "gameObjectType.h"
#include "glfw3.h"
#include "direction.h"


struct GameObject
{
	GameObjectType type;
	GameObjectLayerType layer;
	int action;

	float x; // ���������� �������� ������ ���� ������� (��������)
	float y;
	float spriteX; // ���������� �������� ������ ���� ������� (��������)
	float spriteY;
	float xSpeed;
	float ySpeed;

	float speed;

	int width; // ������ � ������ ������� (��������)
	int height;
	int spriteWidth; // ������ � ������ �������
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
	GameObjectType ownerType; // ��� �������, ���������� ������

	GLuint sprite;

	bool isObjectBusy;
	bool isObjectVisible;
};


/////////////////////////////////////
// ��������� �������
void createGameObject(int indexOfObject);
void gameObjectRender(float dt, int indexOfObject);
void gameObjectUpdate(float dt, int indexOfObject);
float gameObjectSpriteX(int indexOfObject);
float gameObjectSpriteY(int indexOfObject);
void gameObjectIntersect(int indexOfObject, int indexOfOtherObject);
void gameObjectDoDamage(int damage, int indexOfObject);