#pragma once

/////////////////////////////////////
// Подключаемые библиотеки
#include "glfw3.h"
#include "direction.h"
#include <windows.h>
#include "openglLib.h"


/////////////////////////////////////
// Текстуры меню
const char kFolderMenu[] = "Textures/Menu/";
const int kNumberOfSpritesMenu = 8;
const char kTextureMenuLogotype[] = "Logotype.png";
const char kTextureMenuBackgroundName[] = "Background.png";
const char kTextureMenuMilitaryName[] = "Military.png";
const char kTextureMenuMilitaryButtonOffName[] = "ButtonOff.png";
const char kTextureMenuMilitaryButtonOnName[] = "ButtonOn.png";
const char kTextureMenuFloorName[] = "Floor.png";

const char kFolderLoading[] = "Textures/Menu/Loading/";
const char kTextureLoadingBottom[] = "Bottom.png";
const char kTextureLoadingProgressLine[] = "Progress line.png";
const char kTextureLoadingTop[] = "Top.png";

/////////////////////////////////////
// Текстуры Военного
const char kFolderMilitaryRun[] = "Textures/Military/FreeHands/Run/";
const int kNumberOfFramesMilitaryRun = 20;
const int kMilitaryRunWidth = 317;
const int kMilitaryRunHeight = 142;
const int kMilitaryRunAnimationSpeed = 20;

const char kFolderMilitaryPressTheButton[] = "Textures/Military/FreeHands/Press the button/";
const int kNumberOfFramesMilitaryPressTheButton = 100;
const int kMilitaryPressTheButtonWidth = 225;
const int kMilitaryPressTheButtonHeight = 150;
const int kMilitaryPressTheButtonAnimationSpeed = 40;
const int kMilitaryPressTheButtonFrame = 52;


/////////////////////////////////////
// Настроечные константы (НЕ МЕНЯТЬ!!!)
const int kMenuScreenPixelsWidth = 950;
const int kMenuScreenPixelsHeight = 534;

const int kNumberOfMainMenuItems = 4;

const int kMenuButtonLeftTopPixelsX = 83;
const int kMenuButtonLeftTopPixelsY = 192;
const int kMenuButtonPixelsWidth = 260;
const int kMenuButtonPixelsHeight = 20;
const int kMenuDistanceBetweenButtons = 65;

const int kMenuPixelsBetweenFloorButtonX = 9;
const int kMenuPixelsBetweenFloorButtonY = 30;
const int kMenuFloorPixelsWidth = 80;

const int kMenuMilitaryButtonPixelsWidth = 32;
const int kMenuMilitaryButtonPixelsHeight = 32;

const int kDistanceMenuMilitaryButtonX = 20;
const int kDistanceMenuMilitaryButtonY = 20;
const float kMenuMilitarySpriteSize = 4.5f;
const int kMenuMilitaryPixelsSpeed = 50;

const int kLoadingTopWidth = 662;
const int kLoadingTopHeight = 380;
const int kLoadingProgressLineX = 39;
const int kLoadingProgressLineY = 215;
const int kLoadingProgressLineWidth = 582;
const int kLoadingProgressLineHeight = 24;
const double kLoadingScaleFactorX = double(kScreenWidth) / kLoadingTopWidth;
const double kLoadingScaleFactorY = double(kScreenHeight) / kLoadingTopHeight;

const double kScaleFactorX = double(kScreenWidth) / kMenuScreenPixelsWidth;
const double kScaleFactorY = double(kScreenHeight) / kMenuScreenPixelsHeight;

//###################################
const int kPositionOfMenuPixelsX = int(kScaleFactorX * kMenuButtonLeftTopPixelsX);
const int kPositionOfMenuPixelsY = int(kScaleFactorY * kMenuButtonLeftTopPixelsY);
const int kButtonWidth = int(kScaleFactorX * kMenuButtonPixelsWidth);
const int kButtonHeight = int(kScaleFactorY * kMenuButtonPixelsHeight);
const int kDistanceBetweenButtons = int(kScaleFactorY * kMenuDistanceBetweenButtons);

const int kMenuFloorLeftTopPixelsX = int(kPositionOfMenuPixelsX + kButtonWidth + kScaleFactorX * kMenuPixelsBetweenFloorButtonX);
const int kMenuFloorLeftTopPixelsY = int(kPositionOfMenuPixelsY - kScaleFactorY * kMenuPixelsBetweenFloorButtonY);
const int kFloorWidth = int(kScaleFactorX * kMenuFloorPixelsWidth);
const int kFloorHeight = int(kDistanceBetweenButtons * (kNumberOfMainMenuItems - 1) + kButtonHeight + 2 * kScaleFactorY * kMenuPixelsBetweenFloorButtonY);

const int kMilitaryButtonWidth = int(kScaleFactorX * kMenuMilitaryButtonPixelsWidth);
const int kMilitaryButtonHeight = int(kScaleFactorY * kMenuMilitaryButtonPixelsHeight);
const int kMenuMilitaryButtonLeftTopPixelsX = kMenuFloorLeftTopPixelsX;
const int kMenuMilitaryButtonLeftTopPixelsY = int(kPositionOfMenuPixelsY + kButtonHeight / 2 - kMilitaryButtonHeight / 2);
const int kMenuMilitaryDistanceBetweenButtons = kDistanceBetweenButtons;

const int kDistanceMilitaryButtonX = int(kScaleFactorX * kDistanceMenuMilitaryButtonX);
const int kDistanceMilitaryButtonY = int(kScaleFactorY * kDistanceMenuMilitaryButtonY);
const int kMenuMilitaryRunWidth = int(kScaleFactorX * kMilitaryRunWidth / kMenuMilitarySpriteSize);
const int kMenuMilitaryRunHeight = int(kScaleFactorY * kMilitaryRunHeight / kMenuMilitarySpriteSize);
const int kMenuMilitaryPressTheButtonWidth = int(kScaleFactorX * kMilitaryPressTheButtonWidth / kMenuMilitarySpriteSize);
const int kMenuMilitaryPressTheButtonHeight = int(kScaleFactorY * kMilitaryPressTheButtonHeight / kMenuMilitarySpriteSize);
const float kMenuMilitarySpeed = float(kMenuMilitaryPixelsSpeed * kScaleFactorY);
const int kMilitaryRangeOfButton = kDistanceBetweenButtons / 10;

const int kLoadingProgressLinePixelsX = int(kLoadingScaleFactorX * kLoadingProgressLineX);
const int kLoadingProgressLinePixelsY = int(kLoadingScaleFactorY * kLoadingProgressLineY);
const int kLoadingProgressLineWidthPixels = int(kLoadingScaleFactorX * kLoadingProgressLineWidth);
const int kLoadingProgressLineHeightPixels = int(kLoadingScaleFactorY * kLoadingProgressLineHeight);


/////////////////////////////////////
// Константы
const int kMenuKeyDown =	VK_DOWN;
const int kMenuKeyUp =		VK_UP;
const int kMenuKeyEnter =	VK_RETURN;
const int kMenuKeyEsc =		VK_ESCAPE;
const int kMenuButtons[] = { kMenuKeyDown, kMenuKeyUp, kMenuKeyEnter, kMenuKeyEsc };
const int kNumberOfMenuButtons = 4;
const float kMenuMilitaryTurnSpeed = 200.0f;

enum MainMenuItem
{
	MenuItem_1,
	MenuItem_2,
	MenuItem_3,
	MenuItem_4,
};
const int kMenuExit = INT_MAX;

enum MenuObjectType
{
	MenuObjectType_ButtonStartGame,
	MenuObjectType_ButtonOptions,
	MenuObjectType_ButtonAuthors,
	MenuObjectType_ButtonExit,
	MenuObjectType_Military,
	MenuObjectType_Floor,
	MenuObjectType_MilitaryButtonStartGame,
	MenuObjectType_MilitaryButtonOptions,
	MenuObjectType_MilitaryButtonAuthors,
	MenuObjectType_MilitaryButtonExit,

	NumberOfObjectsInMenu
};

enum MenuObjectLayerType
{
	MenuObjectLayerType_Objects,
	MenuObjectLayerType_MilitaryButton,
	MenuObjectLayerType_Military,

	NumberOfMenuObjectLayers
};

enum MenuItemActions
{
	MenuItemActions_Active,
	MenuItemActions_Passive
};

enum MenuMilitaryActions
{
	MenuMilitaryActions_Idle,
	MenuMilitaryActions_Run,
	MenuMilitaryActions_PressTheButton
};


struct MenuObject
{
	MenuObjectType type;
	MenuObjectLayerType layer;
	int action;

	float spriteX;
	float spriteY;

	int width;
	int height;
	double directionAngle;

	GLuint sprite;
};

struct MenuMilitary
{
	float y;
	float ySpeed;
	float currentFrame;
	Direction direction;
};


/////////////////////////////////////
// Прототипы функций
void mainMenuProcess();
void showLoading(float progressPercent);
bool isKeyPressed(const int virtualKeyCode);