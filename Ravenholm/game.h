#pragma once

/////////////////////////////////////
// Подключаемые библиотеки
#include "gameObjectType.h"
#include <glfw3.h>


/////////////////////////////////////
// Константы
const int kObjectsCountMax = 1024;
const int kFramesPerSecond = 30;


/////////////////////////////////////
// Прототипы функций
void gameSetupSystem();
void menuStartTheGameProcess();
float timeBetweenFrames();
bool moveObjectTo(int indexOfObject, float x, float y);
int createObject(GameObjectType objectType, float x, float y, double directionAngle, GLuint texture);