#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
/////////////////////////////////////
// Подключаемые библиотеки
#include "openglLib.h"
#include <math.h>
#include <GL/glut.h>
#include "soil.h"
#include <stdio.h>


/////////////////////////////////////
// Глобальные переменные
GLFWwindow* window;


/////////////////////////////////////
// Функции
bool createWindow(const char *name, const int posX, const int posY)
{ // Возвращает false, если были ошибки при создании окна
	if (!glfwInit())
		return false;

	window = glfwCreateWindow(kScreenWidth,
		kScreenHeight,
		name,
		isFullScreen ? glfwGetPrimaryMonitor() : NULL,
		NULL);

	if (!window)
	{
		glfwTerminate();
		return false;
	}

	glfwSetWindowPos(window, posX, posY);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(window);

	glViewport(0, 0, GLsizei(kScreenWidth), GLsizei(kScreenHeight));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, kScreenWidth, kScreenHeight, 0, 0, 1);
	glfwSwapInterval(1);

	glEnable(GL_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_TEXTURE_2D);

	glPointSize(1);

	return true;
}

bool loadTextures(GLuint *texture, const char *folder, int numberOfFrames)
{ // Возвращает false, если текстура отсутствует
	for (int i = 0; i < numberOfFrames; i++)
	{
		char file[100];
		sprintf(file, "%s%03d.png", folder, i);
		texture[i] = loadTexture(file);
		if (texture[i] == NULL)
			return false;
	}
	return true;
}

GLuint loadSprite(const char *folder, const char *fileName)
{
	char file[100];
	sprintf(file, "%s%s", folder, fileName);
	return loadTexture(file);
}

GLuint loadTexture(const char *apFileName)
{
	GLuint loadingTexture;
	loadingTexture = SOIL_load_OGL_texture(apFileName,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO);
	return loadingTexture;
}

void drawTexture(int aX, int aY, int aW, int aH, GLuint aTextID, bool invert)
{
	int x1 = aX,		y1 = aY;
	int x2 = aX + aW,	y2 = aY;
	int x3 = aX + aW,	y3 = aY + aH;
	int x4 = aX,		y4 = aY + aH;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, aTextID);
	glBegin(GL_QUADS);

	if (invert)
	{
		glTexCoord2i(1, 0); glVertex2i(x1, y1);
		glTexCoord2i(0, 0); glVertex2i(x2, y2);
		glTexCoord2i(0, 1); glVertex2i(x3, y3);
		glTexCoord2i(1, 1); glVertex2i(x4, y4);
	}
	else
	{
		glTexCoord2i(0, 0); glVertex2i(x1, y1);
		glTexCoord2i(1, 0); glVertex2i(x2, y2);
		glTexCoord2i(1, 1); glVertex2i(x3, y3);
		glTexCoord2i(0, 1); glVertex2i(x4, y4);
	}

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawRotateTexture(int aX, int aY, int aW, int aH, GLuint aTextID, double alpha)
{
	double x1 = aX,			y1 = aY;
	double x2 = aX + aW,	y2 = aY;
	double x3 = aX + aW,	y3 = aY + aH;
	double x4 = aX,			y4 = aY + aH;

	double xc = double(x1 + x2 + x3 + x4) / 4.0;
	double yc = double(y1 + y2 + y3 + y4) / 4.0;
	
	double cosA = cos(alpha * M_PI / 180);
	double sinA = sin(alpha * M_PI / 180);

	int x1new = int(xc + ((x1 - xc)*cosA + (y1 - yc)*sinA));
	int y1new = int(yc + ((y1 - yc)*cosA - (x1 - xc)*sinA));

	int x2new = int(xc + ((x2 - xc)*cosA + (y2 - yc)*sinA));
	int y2new = int(yc + ((y2 - yc)*cosA - (x2 - xc)*sinA));

	int x3new = int(xc + ((x3 - xc)*cosA + (y3 - yc)*sinA));
	int y3new = int(yc + ((y3 - yc)*cosA - (x3 - xc)*sinA));

	int x4new = int(xc + ((x4 - xc)*cosA + (y4 - yc)*sinA));
	int y4new = int(yc + ((y4 - yc)*cosA - (x4 - xc)*sinA));

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, aTextID);

	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex2i(x1new, y1new);
	glTexCoord2i(1, 0); glVertex2i(x2new, y2new);
	glTexCoord2i(1, 1); glVertex2i(x3new, y3new);
	glTexCoord2i(0, 1); glVertex2i(x4new, y4new);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}