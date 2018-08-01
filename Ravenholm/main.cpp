/////////////////////////////////////
// Подключаемые библиотеки
#include "game.h"
#include "menu.h"


/////////////////////////////////////
// Pragma
#ifndef _DEBUG
#	pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


/////////////////////////////////////
// Main
int main()
{
	gameSetupSystem();
	
	mainMenuProcess();

	return 0;
}