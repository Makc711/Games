/////////////////////////////////////
// Подключаемые библиотеки
#include "game.h"
#include "gameObjectType.h"
#include "gameObject.h"
#include <stdio.h>  // ?????
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "level.h"
#include <glfw3.h>
#include "openglLib.h"
#include "military.h"
#include "zombie.h"
#include "bullet.h"
#include "textures.h"
#include "mapObjects.h"
#include "aquarium.h"
#include "menu.h"
#include "gameOver.h"


/////////////////////////////////////
// Константы
const int kPositionOfWindowX = 100;
const int kPositionOfWindowY = 80;


/////////////////////////////////////
// Глобальные переменные
bool isGameActive = false;
clock_t clockLastFrame = 0;
GameObject objects[kObjectsCountMax];

GLuint textureBackground[kNumberOfSpritesBackground];

GLuint textureWhiteWall[kNumberOfSpritesWhiteWall];
GLuint textureGlassWall[kNumberOfSpritesGlassWall];

GLuint textureItems[kNumberOfSpritesItems];
GLuint textureAquariumIdle[kNumberOfFramesAquariumIdle];
GLuint textureAquariumBreak[kNumberOfFramesAquariumBreak];

GLuint textureMilitaryAK47Idle[kNumberOfFramesMilitaryAK47Idle];
GLuint textureMilitaryAK47RunningWithAiming[kNumberOfFramesMilitaryAK47RunningWithAiming];
GLuint textureMilitaryAK47Shoot[kNumberOfFramesMilitaryAK47Shoot];
GLuint textureMilitaryAK47Knife[kNumberOfFramesMilitaryAK47Knife];
GLuint textureMilitaryAK47SmallDamage[kNumberOfFramesMilitaryAK47SmallDamage];
GLuint textureMilitaryAK47BigDamage[kNumberOfFramesMilitaryAK47BigDamage];
GLuint textureMilitaryAK47Death[kNumberOfFramesMilitaryAK47Death];

GLuint textureZombieIdle[kNumberOfFramesZombieIdle];
GLuint textureZombieWalk[kNumberOfFramesZombieWalk];
GLuint textureZombieAttac0[kNumberOfFramesZombieAttac0];
GLuint textureZombieAttac1[kNumberOfFramesZombieAttac1];
GLuint textureZombieAttac2[kNumberOfFramesZombieAttac2];
GLuint textureZombieAttac3[kNumberOfFramesZombieAttac3];

GLuint textureYouAreDied;
const int kNumberOfTextures = 20;

extern GLFWwindow *window;
int diedEnemiesCount = 0;
int militaryIndex = 0;
int gameOverIndex = 0;


/////////////////////////////////////
// Прототипы функций
static void newGame();
static void loadGameTextures();
static void gameInitialize();
static bool gameLoop();
static void gameRender(float dt);
static void gameUpdate(float dt);
static void destroyObject(int indexOfObject);
static void setUnitsIndexes();
static void createObjectsInLevel(const char cellSymbol, int c, int r);
static void gameShutdown();
static int checkIntersects(float x, float y, int indexOfObject);


/////////////////////////////////////
// Функции
void gameSetupSystem()
{
	srand(unsigned(time(NULL)));
	const char *nameOfWindow = { "Ravenholm" };
	createWindow(nameOfWindow, kPositionOfWindowX, kPositionOfWindowY);
}

void menuStartTheGameProcess()
{
	newGame();
	loadGameTextures();
	gameInitialize();

	while (gameLoop()) {}

	gameShutdown();
	isGameActive = false;
}

static void newGame()
{
	isGameActive = true;
	clockLastFrame = 0;

	for (int i = 0; i < kObjectsCountMax; i++)
	{
		destroyObject(i);
	}

	diedEnemiesCount = 0;
	militaryIndex = 0;
}

static void loadGameTextures()
{
	float numberOfTexture = 0;
	if (loadTextures(textureBackground, kFolderBackground, kNumberOfSpritesBackground) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureWhiteWall, kFolderWhiteWall, kNumberOfSpritesWhiteWall) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureGlassWall, kFolderGlassWall, kNumberOfSpritesGlassWall) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);

	if (loadTextures(textureItems, kFolderItems, kNumberOfSpritesItems) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureAquariumIdle, kFolderAquariumIdle, kNumberOfFramesAquariumIdle) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureAquariumBreak, kFolderAquariumBreak, kNumberOfFramesAquariumBreak) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);

	if (loadTextures(textureMilitaryAK47Idle, kFolderMilitaryAK47Idle, kNumberOfFramesMilitaryAK47Idle) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureMilitaryAK47RunningWithAiming, kFolderMilitaryAK47RunningWithAiming, kNumberOfFramesMilitaryAK47RunningWithAiming) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureMilitaryAK47Shoot, kFolderMilitaryAK47Shoot, kNumberOfFramesMilitaryAK47Shoot) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureMilitaryAK47Knife, kFolderMilitaryAK47Knife, kNumberOfFramesMilitaryAK47Knife) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureMilitaryAK47SmallDamage, kFolderMilitaryAK47SmallDamage, kNumberOfFramesMilitaryAK47SmallDamage) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureMilitaryAK47BigDamage, kFolderMilitaryAK47BigDamage, kNumberOfFramesMilitaryAK47BigDamage) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureMilitaryAK47Death, kFolderMilitaryAK47Death, kNumberOfFramesMilitaryAK47Death) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);

	if (loadTextures(textureZombieIdle, kFolderZombieIdle, kNumberOfFramesZombieIdle) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureZombieWalk, kFolderZombieWalk, kNumberOfFramesZombieWalk) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureZombieAttac0, kFolderZombieAttac0, kNumberOfFramesZombieAttac0) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureZombieAttac1, kFolderZombieAttac1, kNumberOfFramesZombieAttac1) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureZombieAttac2, kFolderZombieAttac2, kNumberOfFramesZombieAttac2) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
	if (loadTextures(textureZombieAttac3, kFolderZombieAttac3, kNumberOfFramesZombieAttac3) == false)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);

	textureYouAreDied = loadSprite(kFolderMenu, kTextureYouAreDied);
	if (textureYouAreDied == NULL)
		exit(35);
	showLoading(++numberOfTexture / kNumberOfTextures);
}

static void gameInitialize()
{
	gameShutdown();

	// Установить начальное значение clockLastFrame
	clockLastFrame = clock();

	diedEnemiesCount = 0;

	// Загрузка уровня
	for (int r = 0; r < kLevelRows; r++)
	{
		for (int c = 0; c < kLevelColumns; c++)
		{
			const char cellSymbol = kLevelData0[r][c];
			createObjectsInLevel(cellSymbol, c, r);
		}
	}
	createGameOverLable();

	setUnitsIndexes();
}

static void createObjectsInLevel(const char cellSymbol, int c, int r)
{
	switch (cellSymbol)
	{
		case CellSymbol_Tile0:
			createObject(GameObjectType_Tile, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureBackground[BackgroundType_Tile0]);
			break;

		case CellSymbol_Wall0:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureWhiteWall[WallType_Wall]);
			break;
		case CellSymbol_Wall1:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 90, textureWhiteWall[WallType_Wall]);
			break;
		case CellSymbol_Wall2:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureWhiteWall[WallType_Angle]);
			break;
		case CellSymbol_Wall3:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 90, textureWhiteWall[WallType_Angle]);
			break;
		case CellSymbol_Wall4:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 180, textureWhiteWall[WallType_Angle]);
			break;
		case CellSymbol_Wall5:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 270, textureWhiteWall[WallType_Angle]);
			break;
		case CellSymbol_Wall6:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureWhiteWall[WallType_End]);
			break;
		case CellSymbol_Wall7:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 90, textureWhiteWall[WallType_End]);
			break;
		case CellSymbol_Wall8:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 180, textureWhiteWall[WallType_End]);
			break;
		case CellSymbol_Wall9:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 270, textureWhiteWall[WallType_End]);
			break;
		case CellSymbol_Wall10:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureWhiteWall[WallType_Three]);
			break;
		case CellSymbol_Wall11:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 90, textureWhiteWall[WallType_Three]);
			break;
		case CellSymbol_Wall12:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 180, textureWhiteWall[WallType_Three]);
			break;
		case CellSymbol_Wall13:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 270, textureWhiteWall[WallType_Three]);
			break;
		case CellSymbol_Wall14:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureWhiteWall[WallType_Cross]);
			break;
		case CellSymbol_Glass0:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureGlassWall[GlassWallType_Wall]);
			break;
		case CellSymbol_Glass1:
			createObject(GameObjectType_Wall, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 90, textureGlassWall[GlassWallType_Wall]);
			break;

		case CellSymbol_Table0:
			createObject(GameObjectType_Table, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 90, textureItems[ItemType_TableWithObjects]);
			break;
		case CellSymbol_Computer0:
			createObject(GameObjectType_Computer0, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Computer0]);
			break;
		case CellSymbol_Computer1:
			createObject(GameObjectType_Computer1, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 180, textureItems[ItemType_Computer1]);
			break;
		case CellSymbol_Chair:
			createObject(GameObjectType_Chair, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 90, textureItems[ItemType_Chair]);
			break;
		case CellSymbol_Bin:
			createObject(GameObjectType_Bin, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Bin]);
			break;
		case CellSymbol_Generator:
			createObject(GameObjectType_Generator0, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Generator0]);
			break;
		case CellSymbol_Arc:
			createObject(GameObjectType_Arc, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Arc]);
			break;
		case CellSymbol_Danger0:
			createObject(GameObjectType_Danger, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Danger0]);
			break;
		case CellSymbol_Reactor2:
			createObject(GameObjectType_Reactor, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Reactor2]);
			break;
		case CellSymbol_Generator2:
			createObject(GameObjectType_Generator2, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Generator2]);
			break;
		case CellSymbol_Reactor0:
			createObject(GameObjectType_Reactor, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Reactor0]);
			break;
		case CellSymbol_Reactor1:
			createObject(GameObjectType_Reactor, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Reactor1]);
			break;
		case CellSymbol_Sewerage0:
			createObject(GameObjectType_Sewerage, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Sewerage0]);
			break;
		case CellSymbol_Sewerage1:
			createObject(GameObjectType_Sewerage, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Sewerage1]);
			break;
		case CellSymbol_Puddle0:
			createObject(GameObjectType_Sewerage, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Puddle0]);
			break;
		case CellSymbol_Puddle1:
			createObject(GameObjectType_Sewerage, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Puddle1]);
			break;
		case CellSymbol_Puddle2:
			createObject(GameObjectType_Sewerage, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Puddle2]);
			break;
		case CellSymbol_DoorFell:
			createObject(GameObjectType_DoorFell, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), -10, textureItems[ItemType_DoorFell]);
			break;
		case CellSymbol_DoorOpened:
			createObject(GameObjectType_DoorOpened, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_DoorOpened]);
			break;
		case CellSymbol_Door0:
			createObject(GameObjectType_Door, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Door0]);
			break;

		case CellSymbol_Corpse0:
			createObject(GameObjectType_Corpse, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, textureItems[ItemType_Corpse0]);
			break;
		case CellSymbol_Corpse1:
			createObject(GameObjectType_Corpse, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 90, textureItems[ItemType_Corpse1]);
			break;
		case CellSymbol_Corpse2:
			createObject(GameObjectType_Corpse, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 90, textureItems[ItemType_Corpse2]);
			break;

		case CellSymbol_Aquarium:
			createObject(GameObjectType_Aquarium, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, 0);
			break;

		case CellSymbol_Military:
			createObject(GameObjectType_Military, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, 0);
			militarySetKeys('A', 'D', 'W', 'S', VK_SPACE, 'E');
			break;
		case CellSymbol_Zombie:
			createObject(GameObjectType_Zombie, float(c * kPixelsPerCell + kPixelsOnLeft), float(r * kPixelsPerCell + kPixelsOnTop), 0, 0);
			break;
	}
}

static bool gameLoop()
{
	if (glfwWindowShouldClose(window) || isKeyPressed(VK_ESCAPE))
	{
		return false;
	}

	float deltaTime = timeBetweenFrames();

	gameRender(deltaTime);
	gameUpdate(deltaTime);

	return isGameActive;
}

float timeBetweenFrames()
{
	clock_t clockNow = 0;
	clock_t deltaClock = 0;
	if (isGameActive)
	{
		clockNow = clock();
		deltaClock = clockNow - clockLastFrame;
	}
	else
	{
		while (deltaClock < CLOCKS_PER_SEC / kFramesPerSecond)
		{
			clockNow = clock();
			deltaClock = clockNow - clockLastFrame;
		}
	}
	
	clockLastFrame = clockNow;
	return float(deltaClock) / CLOCKS_PER_SEC;
}

int createObject(GameObjectType objectType, float x, float y, double directionAngle, GLuint texture)
{
	// Найти свободное место и создать объект
	for (int i = 0; i < kObjectsCountMax; i++)
	{
		if (objects[i].isObjectBusy == false)
		{
			switch (objectType)
			{
				case GameObjectType_Tile:
					createGameObject(i);
					objects[i].type = GameObjectType_Tile;
					objects[i].layer = GameObjectLayerType_Background;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 0;
					objects[i].height = 0;
					objects[i].spriteWidth = 6 * kPixelsPerCell;
					objects[i].spriteHeight = 6 * kPixelsPerCell;
					objects[i].spriteX = gameObjectSpriteX(i);
					objects[i].spriteY = gameObjectSpriteY(i);
					objects[i].directionAngle = directionAngle;
					objects[i].physical = false;
					break;

				case GameObjectType_Wall:
					createGameObject(i);
					objects[i].type = GameObjectType_Wall;
					objects[i].layer = GameObjectLayerType_Walls;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].directionAngle = directionAngle;
					break;
				case GameObjectType_Glass:
					createGameObject(i);
					objects[i].type = GameObjectType_Glass;
					objects[i].layer = GameObjectLayerType_Walls;
					objects[i].sprite = texture;
					objects[i].directionAngle = directionAngle;
					break;

				case GameObjectType_Table:
					createGameObject(i);
					objects[i].type = GameObjectType_Table;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 3 * kPixelsPerCell;
					objects[i].height = 6 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].height;
					objects[i].spriteHeight = objects[i].width;
					objects[i].directionAngle = directionAngle;
					break;
				case GameObjectType_Computer0:
					createGameObject(i);
					objects[i].type = GameObjectType_Computer0;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 3 * kPixelsPerCell;
					objects[i].height = 12 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					break;
				case GameObjectType_Computer1:
					createGameObject(i);
					objects[i].type = GameObjectType_Computer1;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 2 * kPixelsPerCell;
					objects[i].height = 7 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					break;
				case GameObjectType_Chair:
					createGameObject(i);
					objects[i].type = GameObjectType_Chair;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 2 * kPixelsPerCell;
					objects[i].height = 2 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					break;
				case GameObjectType_Bin:
					createGameObject(i);
					objects[i].type = GameObjectType_Bin;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 2 * kPixelsPerCell;
					objects[i].height = 2 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					break;
				case GameObjectType_Generator0:
					createGameObject(i);
					objects[i].type = GameObjectType_Generator0;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 7 * kPixelsPerCell;
					objects[i].height = 4 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					break;
				case GameObjectType_Arc:
					createGameObject(i);
					objects[i].type = GameObjectType_Arc;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 6 * kPixelsPerCell;
					objects[i].height = 2 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					objects[i].physical = false;
					break;
				case GameObjectType_Danger:
					createGameObject(i);
					objects[i].type = GameObjectType_Danger;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 2 * kPixelsPerCell;
					objects[i].height = 2 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					objects[i].physical = false;
					break;
				case GameObjectType_Reactor:
					createGameObject(i);
					objects[i].type = GameObjectType_Reactor;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 4 * kPixelsPerCell;
					objects[i].height = 4 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					break;
				case GameObjectType_Generator2:
					createGameObject(i);
					objects[i].type = GameObjectType_Generator2;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 12 * kPixelsPerCell;
					objects[i].height = 4 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					break;
				case GameObjectType_Sewerage:
					createGameObject(i);
					objects[i].type = GameObjectType_Sewerage;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 4 * kPixelsPerCell;
					objects[i].height = 4 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					objects[i].physical = false;
					break;
				case GameObjectType_DoorFell:
					createGameObject(i);
					objects[i].type = GameObjectType_DoorFell;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 3 * kPixelsPerCell;
					objects[i].height = 6 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					objects[i].physical = false;
					break;
				case GameObjectType_DoorOpened:
					createGameObject(i);
					objects[i].type = GameObjectType_DoorOpened;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 1 * kPixelsPerCell;
					objects[i].height = 3 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					break;
				case GameObjectType_Door:
					createGameObject(i);
					objects[i].type = GameObjectType_Door;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 1 * kPixelsPerCell;
					objects[i].height = 3 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					break;
				case GameObjectType_Corpse:
					createGameObject(i);
					objects[i].type = GameObjectType_Corpse;
					objects[i].layer = GameObjectLayerType_Objects;
					objects[i].invulnerable = true;
					objects[i].sprite = texture;
					objects[i].width = 6 * kPixelsPerCell;
					objects[i].height = 6 * kPixelsPerCell;
					objects[i].spriteWidth = objects[i].width;
					objects[i].spriteHeight = objects[i].height;
					objects[i].directionAngle = directionAngle;
					objects[i].physical = false;
					break;

				case GameObjectType_Aquarium:
					createAquarium(i);
					break;

				case GameObjectType_Military:
					createMilitary(i);
					break;
				case GameObjectType_Zombie:
					createZombie(i);
					break;

				case GameObjectType_Bullet:
					createBullet(i);
					break;

				default:
					return -1;
			}

			if (moveObjectTo(i, x, y) == false)
			{
				destroyObject(i);
				return -1;
			}

			objects[i].isObjectBusy = true;
			objects[i].isObjectVisible = true;

			return i;
		}
	}
	return -1;
}

static void setUnitsIndexes()
{
	for (int i = 0; i < kObjectsCountMax; i++)
	{
		if (objects[i].isObjectBusy)
		{
			switch (objects[i].type)
			{
				case GameObjectType_Military:
					militaryIndex = i;
					break;
				case GameObjectType_GameOver:
					gameOverIndex = i;
					break;
			}
		}
	}
}

static void gameShutdown()
{
	for (int i = 0; i < kObjectsCountMax; i++)
	{
		if (objects[i].isObjectBusy)
		{
			destroyObject(i);
		}
	}
}

static void destroyObject(int indexOfObject)
{
	objects[indexOfObject].type = GameObjectType_None;
	objects[indexOfObject].layer = GameObjectLayerType_Background;
	objects[indexOfObject].action = 0;

	objects[indexOfObject].x = 0.0f;
	objects[indexOfObject].y = 0.0f;
	objects[indexOfObject].spriteX = 0.0f;
	objects[indexOfObject].spriteY = 0.0f;
	objects[indexOfObject].xSpeed = 0.0f;
	objects[indexOfObject].ySpeed = 0.0f;

	objects[indexOfObject].speed = 0.0f;

	objects[indexOfObject].width = 0;
	objects[indexOfObject].height = 0;
	objects[indexOfObject].spriteWidth = 0;
	objects[indexOfObject].spriteHeight = 0;
	objects[indexOfObject].currentFrame = 0.0f;

	objects[indexOfObject].health = 0;
	objects[indexOfObject].destroyAfterDeath = false;
	objects[indexOfObject].invulnerable = false;

	objects[indexOfObject].physical = false;
	objects[indexOfObject].scratchingTime = 0.0f;
	objects[indexOfObject].fireCooldownTime = 0.0f;

	objects[indexOfObject].direction = Direction_Right;
	objects[indexOfObject].directionAngle = 0.0;
	objects[indexOfObject].ownerType = GameObjectType_None;

	objects[indexOfObject].sprite = 0;

	objects[indexOfObject].isObjectBusy = false;
	objects[indexOfObject].isObjectVisible = false;
}

static void gameRender(float dt)
{
	// Начало кадра
	glClearColor(0.0f, 0.0f, 0.0f, 0); // Цвет фона
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Рисуем все игровые объекты
	int objectsCount = 0;
	for (int l = 0; l < NumberOfGameObjectLayers; l++)
	{
		for (int i = 0; i < kObjectsCountMax; i++)
		{
			if (objects[i].isObjectVisible && objects[i].layer == l)
			{
				gameObjectRender(dt, i);
				objectsCount++;
			}
		}
	}

	// Конец кадра
	glfwSwapBuffers(window);
	glfwPollEvents();
}

static void gameUpdate(float dt)
{
	for (int i = 0; i < kObjectsCountMax; i++)
	{
		if (objects[i].isObjectBusy)
		{
			switch (objects[i].type)
			{
				case GameObjectType_Aquarium:
					aquariumUpdate(dt, i);
					break;
				case GameObjectType_Military:
					militaryUpdate(dt, i);
					break;
				case GameObjectType_Zombie:
					zombieUpdate(dt, i);
					break;
				case GameObjectType_GameOver:
					updateGameOverLable(dt, i);
					break;
				default:
					gameObjectUpdate(dt, i);
			}

			if (objects[i].health <= 0 && objects[i].destroyAfterDeath)
			{
				destroyObject(i);
			}
		}
	}
	
	// Военный уничтожен
	if (objects[militaryIndex].health <= 0)
	{
		objects[gameOverIndex].isObjectVisible = true;
	}
}

bool moveObjectTo(int indexOfObject, float x, float y)
{
	int x0 = int(x);
	int y0 = int(y);
	int x1 = x0 + objects[indexOfObject].width - 1;
	int y1 = y0 + objects[indexOfObject].height - 1;

	if ( x0 < 0 || y0 < 0 || x1 >= kScreenWidth || y1 >= kScreenHeight)
		return false;

	bool canMoveToCell = false;
	int indexOfOtherObject = -1;
	if (objects[indexOfObject].physical)
	{
		indexOfOtherObject = checkIntersects(x, y, indexOfObject);
	}
	
	if (indexOfOtherObject != -1)
	{
		gameObjectIntersect(indexOfObject, indexOfOtherObject);
	}
	else
	{
		canMoveToCell = true;
	}

	if (canMoveToCell)
	{
		objects[indexOfObject].x = x;
		objects[indexOfObject].y = y;
	}

	return canMoveToCell;
}

static int checkIntersects(float x, float y, int indexOfObject)
{
	int x00 = int(x);
	int y00 = int(y);
	int x01 = x00 + objects[indexOfObject].width - 1;
	int y01 = y00 + objects[indexOfObject].height - 1;

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