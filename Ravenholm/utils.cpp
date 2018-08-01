/////////////////////////////////////
// Подключаемые библиотеки
#include "utils.h"
#include <Windows.h>
#include <GL/glut.h>


/////////////////////////////////////
// Функции
bool isKeyDown(const int virtualKeyCode)
{
	short keyState = GetAsyncKeyState(virtualKeyCode);
	return ((keyState & (1 << 15)) > 0);
}

int getRandomInt(int min, int max)
{
	return min + rand() % (max - min + 1);
}

float getRandomFloat(float min, float max)
{
	return (min + (max - min) * (float(rand() % 101) / 100.0f));
}