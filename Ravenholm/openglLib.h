#pragma once

/////////////////////////////////////
// Подключаемые библиотеки
#include "glfw3.h"


/////////////////////////////////////
// Константы
const int kScreenWidth = 1366;
const int kScreenHeight = 768;
const int isFullScreen = true;


/////////////////////////////////////
// Функции
bool createWindow(const char *name, const int posX, const int posY);
GLuint loadTexture(const char *apFileName);
GLuint loadSprite(const char *folder, const char *fileName);
bool loadTextures(GLuint *texture, const char *folder, int numberOfFrames);

void drawTexture(int aX, int aY, int aW, int aH, GLuint aTextID, bool invert);
void drawRotateTexture(int aX, int aY, int aW, int aH, GLuint aTextID, double alpha);