#pragma once

/////////////////////////////////////
// Подключаемые библиотеки
#include "direction.h"
#include "gameObject.h"

/////////////////////////////////////
// Прототипы функций
void update(float dt, int indexOfObject, float unitTurnSpeed);
void move(Direction direction, int indexOfObject);
void scratch(int indexOfObject, int indexOfTargetObject, int damage, float recoveryTime);
bool fire(int indexOfObject);
void moveRandomDirection(int indexOfObject);
int findDistanceToObject(float *distance, int indexOfObject);
void changeAction(int indexOfObject, int action);
void changeFrame(float dt, int indexOfObject, int idleAction, GLuint *texture, int numberOfFrames, int animationSpeed);
void setUnitSpriteWidth(int indexOfObject, const int spriteWidthPixels, const int spriteSize);
void setUnitSpriteHeight(int indexOfObject, const int spriteHeightPixels, const int spriteSize);
double calculateDirectionAngle(double unitDirectionAngle, float turningAngle, int alpha);