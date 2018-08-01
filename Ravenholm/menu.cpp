#define _CRT_SECURE_NO_WARNINGS
/////////////////////////////////////
// Подключаемые библиотеки
#include "menu.h"
#include <glfw3.h>
#include "openglLib.h"
#include <stdlib.h>
#include "game.h"
#include "utils.h"
#include "unitsActions.h"


/////////////////////////////////////
// Глобальные переменные
extern GLFWwindow* window;
bool isMenuActive = true;
int lastPressedKeyCode = NULL;
bool buttonPressed = false;
bool militaryPressTheButton = false;

GLuint textureMenuLogotype;
GLuint textureLoadingBottom;
GLuint textureLoadingProgressLine;
GLuint textureLoadingTop;
GLuint textureMenu[kNumberOfSpritesMenu];
GLuint textureMenuBackground;
GLuint textureMenuMilitaryButtonOff;
GLuint textureMenuMilitaryButtonOn;
GLuint textureMenuFloor;
GLuint textureMenuMilitaryIdle;
GLuint textureMenuMilitaryRun[kNumberOfFramesMilitaryRun];
GLuint textureMenuMilitaryPressTheButton[kNumberOfFramesMilitaryPressTheButton];
MenuObject menuObjects[NumberOfObjectsInMenu];
MenuMilitary menuMilitary;


/////////////////////////////////////
// Прототипы функций
static void showLogotype();
static void loadMenuTextures();
static void createObjectsInMenu();
static bool menuLoop();
static void menuRender(float dt);
static void menuObjectRender(float dt, int indexOfObject);
static void createMenuObject(int indexOfObject);
static void createButton(int indexOfObject, MenuObjectType objectType);
static void createMenuMilitary(int indexOfObject);
static void menuMilitaryRender(float dt, int indexOfObject);
static bool changeMenuFrame(float dt, int indexOfObject, int idleAction, GLuint *texture, const int numberOfFrames, const int animationSpeed);
static void setButtonSprite(int indexOfObject);
static void setMilitaryButtonSprite(int indexOfObject);
static void menuUpdate(float dt);
static void menuMilitaryUpdate(float dt, int indexOfObject);
static void militaryPositionUpdate(float dt, int indexOfObject);
static void changeMenuObjectAction(int indexOfObject, int action);
static void setMenuMilitarySpriteSize(int indexOfObject);
static int moveMenuMilitary(float dt, int indexOfObject);
static void createMenuFloor(int indexOfObject);
static void createMenuMilitaryButton(int indexOfObject, MenuObjectType objectType);
static void setButtonActive(MenuObjectType objectType);
static void setMilitaryButtonActive(MenuObjectType objectType);
static void setMilitaryButtonPassive();
static int stateWait(int numberOfItems, int selectItemState);
static int stateDisplay(const int numberOfItems, const int selectItemState);
static int jumpToSelectItem(int numberOfItems, int selectItemState);


/////////////////////////////////////
// Функции
void mainMenuProcess()
{
	showLogotype();
	loadMenuTextures();
	createObjectsInMenu();

	int menuStatus = MenuItem_1;
	const int numberOfItems = kNumberOfMainMenuItems;
	while (menuLoop())
	{
		switch (menuStatus)
		{
			case MenuItem_1:
				setButtonActive(MenuObjectType_ButtonStartGame);
				menuStatus = stateWait(numberOfItems, menuStatus);
				break;
			case numberOfItems + MenuItem_1:
				menuStatus = jumpToSelectItem(numberOfItems, menuStatus);
				break;
			case numberOfItems + numberOfItems + MenuItem_1:
				buttonPressed = true;
				setMilitaryButtonActive(MenuObjectType_MilitaryButtonStartGame);
				if (militaryPressTheButton)
				{
					buttonPressed = false;
					militaryPressTheButton = false;
					showLoading(0.0f);
					menuStartTheGameProcess();
					setMilitaryButtonPassive();
					menuStatus = stateDisplay(numberOfItems, menuStatus);
				}
				break;

			case MenuItem_2:
				setButtonActive(MenuObjectType_ButtonOptions);
				menuStatus = stateWait(numberOfItems, menuStatus);
				break;
			case numberOfItems + MenuItem_2:
				menuStatus = jumpToSelectItem(numberOfItems, menuStatus);
				break;
			case numberOfItems + numberOfItems + MenuItem_2:
				buttonPressed = true;
				setMilitaryButtonActive(MenuObjectType_MilitaryButtonOptions);
				if (militaryPressTheButton)
				{
					buttonPressed = false;
					militaryPressTheButton = false;
//					menuOptionsProcess();
					setMilitaryButtonPassive();
					menuStatus = stateDisplay(numberOfItems, menuStatus);
				}
				break;

			case MenuItem_3:
				setButtonActive(MenuObjectType_ButtonAuthors);
				menuStatus = stateWait(numberOfItems, menuStatus);
				break;
			case numberOfItems + MenuItem_3:
				menuStatus = jumpToSelectItem(numberOfItems, menuStatus);
				break;
			case numberOfItems + numberOfItems + MenuItem_3:
				buttonPressed = true;
				setMilitaryButtonActive(MenuObjectType_MilitaryButtonAuthors);
				if (militaryPressTheButton)
				{
					buttonPressed = false;
					militaryPressTheButton = false;
//					menuAuthorsProcess();
					setMilitaryButtonPassive();
					menuStatus = stateDisplay(numberOfItems, menuStatus);
				}
				break;

			case MenuItem_4:
				setButtonActive(MenuObjectType_ButtonExit);
				menuStatus = stateWait(numberOfItems, menuStatus);
				break;
			case numberOfItems + MenuItem_4:
				menuStatus = jumpToSelectItem(numberOfItems, menuStatus);
				break;
			case numberOfItems + numberOfItems + MenuItem_4:
				buttonPressed = true;
				setMilitaryButtonActive(MenuObjectType_MilitaryButtonExit);
				if (militaryPressTheButton)
				{
					buttonPressed = false;
					militaryPressTheButton = false;
					exit(0);
				}
				break;

			default:
				exit(0);
		}
	}
}

static void showLogotype()
{
	textureMenuLogotype = loadSprite(kFolderMenu, kTextureMenuLogotype);
	if (textureMenuLogotype == NULL)
		exit(35);

	// Начало кадра
	glClearColor(0.4f, 0.6156862f, 0.0901961f, 0); // Цвет фона
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	const int screenSize = (kScreenHeight <= kScreenWidth) ? kScreenHeight : kScreenWidth;
	drawTexture(kScreenWidth / 2 - screenSize / 2, 0, screenSize, screenSize, textureMenuLogotype, false);

	// Конец кадра
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void showLoading(float progressPercent)
{
	// Начало кадра
	glClearColor(0.0f, 0.0f, 0.0f, 0); // Цвет фона
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int progress = int(progressPercent * kLoadingProgressLineWidthPixels);
	drawTexture(kLoadingProgressLinePixelsX, kLoadingProgressLinePixelsY, kLoadingProgressLineWidthPixels, kLoadingProgressLineHeightPixels, textureLoadingBottom, false);
	drawTexture(kLoadingProgressLinePixelsX - kLoadingProgressLineWidthPixels + progress, kLoadingProgressLinePixelsY, kLoadingProgressLineWidthPixels, kLoadingProgressLineHeightPixels, textureLoadingProgressLine, false);
	drawTexture(0, 0, kScreenWidth, kScreenHeight, textureLoadingTop, false);

	// Конец кадра
	glfwSwapBuffers(window);
	glfwPollEvents();
}

static void loadMenuTextures()
{
	textureLoadingBottom = loadSprite(kFolderLoading, kTextureLoadingBottom);
	if (textureLoadingBottom == NULL)
		exit(35);
	textureLoadingProgressLine = loadSprite(kFolderLoading, kTextureLoadingProgressLine);
	if (textureLoadingProgressLine == NULL)
		exit(35);
	textureLoadingTop = loadSprite(kFolderLoading, kTextureLoadingTop);
	if (textureLoadingTop == NULL)
		exit(35);
	if (loadTextures(textureMenu, kFolderMenu, kNumberOfSpritesMenu) == false)
		exit(35);
	textureMenuBackground = loadSprite(kFolderMenu, kTextureMenuBackgroundName);
	if (textureMenuBackground == NULL)
		exit(35);
	textureMenuMilitaryButtonOff = loadSprite(kFolderMenu, kTextureMenuMilitaryButtonOffName);
	if (textureMenuMilitaryButtonOff == NULL)
		exit(35);
	textureMenuMilitaryButtonOn = loadSprite(kFolderMenu, kTextureMenuMilitaryButtonOnName);
	if (textureMenuMilitaryButtonOn == NULL)
		exit(35);
	textureMenuFloor = loadSprite(kFolderMenu, kTextureMenuFloorName);
	if (textureMenuFloor == NULL)
		exit(35);

	textureMenuMilitaryIdle = loadSprite(kFolderMenu, kTextureMenuMilitaryName);
	if (textureMenuMilitaryIdle == NULL)
		exit(35);
	if (loadTextures(textureMenuMilitaryRun, kFolderMilitaryRun, kNumberOfFramesMilitaryRun) == false)
		exit(35);
	if (loadTextures(textureMenuMilitaryPressTheButton, kFolderMilitaryPressTheButton, kNumberOfFramesMilitaryPressTheButton) == false)
		exit(35);
}

static void createObjectsInMenu()
{
	for (int indexOfMenuObject = 0; indexOfMenuObject < NumberOfObjectsInMenu; indexOfMenuObject++)
	{
		switch (indexOfMenuObject)
		{
			case MenuObjectType_ButtonStartGame:
				createButton(indexOfMenuObject, MenuObjectType_ButtonStartGame);
				menuObjects[indexOfMenuObject].spriteX = float(kPositionOfMenuPixelsX);
				menuObjects[indexOfMenuObject].spriteY = float(kPositionOfMenuPixelsY + MenuItem_1 * kDistanceBetweenButtons);
				break;
			case MenuObjectType_ButtonOptions:
				createButton(indexOfMenuObject, MenuObjectType_ButtonOptions);
				menuObjects[indexOfMenuObject].spriteX = float(kPositionOfMenuPixelsX);
				menuObjects[indexOfMenuObject].spriteY = float(kPositionOfMenuPixelsY + MenuItem_2 * kDistanceBetweenButtons);
				break;
			case MenuObjectType_ButtonAuthors:
				createButton(indexOfMenuObject, MenuObjectType_ButtonAuthors);
				menuObjects[indexOfMenuObject].spriteX = float(kPositionOfMenuPixelsX);
				menuObjects[indexOfMenuObject].spriteY = float(kPositionOfMenuPixelsY + MenuItem_3 * kDistanceBetweenButtons);
				break;
			case MenuObjectType_ButtonExit:
				createButton(indexOfMenuObject, MenuObjectType_ButtonExit);
				menuObjects[indexOfMenuObject].spriteX = float(kPositionOfMenuPixelsX);
				menuObjects[indexOfMenuObject].spriteY = float(kPositionOfMenuPixelsY + MenuItem_4 * kDistanceBetweenButtons);
				break;
			case MenuObjectType_Military:
				createMenuMilitary(indexOfMenuObject);
				menuObjects[indexOfMenuObject].spriteX = float(kPositionOfMenuPixelsX + kButtonWidth + kDistanceMilitaryButtonX);
				menuObjects[indexOfMenuObject].spriteY = float(kPositionOfMenuPixelsY - kDistanceMilitaryButtonY);
				break;
			case MenuObjectType_Floor:
				createMenuFloor(indexOfMenuObject);
				menuObjects[indexOfMenuObject].spriteX = float(kMenuFloorLeftTopPixelsX);
				menuObjects[indexOfMenuObject].spriteY = float(kMenuFloorLeftTopPixelsY);
				break;
			case MenuObjectType_MilitaryButtonStartGame:
				createMenuMilitaryButton(indexOfMenuObject, MenuObjectType_MilitaryButtonStartGame);
				menuObjects[indexOfMenuObject].spriteX = float(kMenuMilitaryButtonLeftTopPixelsX);
				menuObjects[indexOfMenuObject].spriteY = float(kMenuMilitaryButtonLeftTopPixelsY + MenuItem_1 * kMenuMilitaryDistanceBetweenButtons);
				break;
			case MenuObjectType_MilitaryButtonOptions:
				createMenuMilitaryButton(indexOfMenuObject, MenuObjectType_MilitaryButtonOptions);
				menuObjects[indexOfMenuObject].spriteX = float(kMenuMilitaryButtonLeftTopPixelsX);
				menuObjects[indexOfMenuObject].spriteY = float(kMenuMilitaryButtonLeftTopPixelsY + MenuItem_2 * kMenuMilitaryDistanceBetweenButtons);
				break;
			case MenuObjectType_MilitaryButtonAuthors:
				createMenuMilitaryButton(indexOfMenuObject, MenuObjectType_MilitaryButtonAuthors);
				menuObjects[indexOfMenuObject].spriteX = float(kMenuMilitaryButtonLeftTopPixelsX);
				menuObjects[indexOfMenuObject].spriteY = float(kMenuMilitaryButtonLeftTopPixelsY + MenuItem_3 * kMenuMilitaryDistanceBetweenButtons);
				break;
			case MenuObjectType_MilitaryButtonExit:
				createMenuMilitaryButton(indexOfMenuObject, MenuObjectType_MilitaryButtonExit);
				menuObjects[indexOfMenuObject].spriteX = float(kMenuMilitaryButtonLeftTopPixelsX);
				menuObjects[indexOfMenuObject].spriteY = float(kMenuMilitaryButtonLeftTopPixelsY + MenuItem_4 * kMenuMilitaryDistanceBetweenButtons);
				break;
		}
	}
}

static void createMenuObject(int indexOfObject)
{
	menuObjects[indexOfObject].type = MenuObjectType_ButtonStartGame;
	menuObjects[indexOfObject].layer = MenuObjectLayerType_Objects;
	menuObjects[indexOfObject].action = MenuItemActions_Passive;

	menuObjects[indexOfObject].spriteX = 0.0f;
	menuObjects[indexOfObject].spriteY = 0.0f;

	menuObjects[indexOfObject].width = kButtonWidth;
	menuObjects[indexOfObject].height = kButtonHeight;
	menuObjects[indexOfObject].directionAngle = 0.0;

	menuObjects[indexOfObject].sprite = 0;
}

static void createButton(int indexOfObject, MenuObjectType objectType)
{
	createMenuObject(indexOfObject);

	menuObjects[indexOfObject].type = objectType;
	setButtonSprite(indexOfObject);
}

static void createMenuMilitary(int indexOfObject)
{
	createMenuObject(indexOfObject);

	menuObjects[indexOfObject].type = MenuObjectType_Military;
	menuObjects[indexOfObject].layer = MenuObjectLayerType_Military;
	menuObjects[indexOfObject].action = MenuMilitaryActions_Idle;
	menuObjects[indexOfObject].width = kMilitaryPressTheButtonWidth;
	menuObjects[indexOfObject].height = kMilitaryPressTheButtonHeight;
	menuObjects[indexOfObject].directionAngle = 180.0;

	menuMilitary.y = float(kPositionOfMenuPixelsY);
	menuMilitary.ySpeed = 0.0f;
	menuMilitary.currentFrame = 0.0f;
	menuMilitary.direction = Direction_Left;

	menuMilitaryRender(0, indexOfObject);
}

static void createMenuFloor(int indexOfObject)
{
	createMenuObject(indexOfObject);

	menuObjects[indexOfObject].type = MenuObjectType_Floor;
	menuObjects[indexOfObject].width = kFloorWidth;
	menuObjects[indexOfObject].height = kFloorHeight;
	menuObjects[indexOfObject].sprite = textureMenuFloor;
}

static void createMenuMilitaryButton(int indexOfObject, MenuObjectType objectType)
{
	createMenuObject(indexOfObject);

	menuObjects[indexOfObject].type = objectType;
	menuObjects[indexOfObject].layer = MenuObjectLayerType_MilitaryButton;
	menuObjects[indexOfObject].width = kMilitaryButtonWidth;
	menuObjects[indexOfObject].height = kMilitaryButtonHeight;
	setMilitaryButtonSprite(indexOfObject);
}

static void setButtonSprite(int indexOfObject)
{
	switch (menuObjects[indexOfObject].action)
	{
		case MenuItemActions_Active:
			menuObjects[indexOfObject].sprite = textureMenu[menuObjects[indexOfObject].type];
			break;
		case MenuItemActions_Passive:
			menuObjects[indexOfObject].sprite = textureMenu[menuObjects[indexOfObject].type + kNumberOfMainMenuItems];
			break;
	}
}

static void setMilitaryButtonSprite(int indexOfObject)
{
	switch (menuObjects[indexOfObject].action)
	{
		case MenuItemActions_Active:
			menuObjects[indexOfObject].sprite = textureMenuMilitaryButtonOn;
			break;
		case MenuItemActions_Passive:
			menuObjects[indexOfObject].sprite = textureMenuMilitaryButtonOff;
			break;
	}
}

static bool menuLoop()
{
	if (glfwWindowShouldClose(window))
	{
		return false;
	}

	float deltaTime = timeBetweenFrames();

	menuRender(deltaTime);
	menuUpdate(deltaTime);

	return isMenuActive;
}

static void menuRender(float dt)
{
	// Начало кадра
	glClearColor(0.0f, 0.0f, 0.0f, 0); // Цвет фона
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawTexture(0, 0, kScreenWidth, kScreenHeight, textureMenuBackground, false);
	// Рисуем все объекты меню
	for (int l = 0; l < NumberOfMenuObjectLayers; l++)
	{
		for (int i = 0; i < NumberOfObjectsInMenu; i++)
		{
			if (menuObjects[i].layer == l)
			{
				menuObjectRender(dt, i);
			}
		}
	}

	// Конец кадра
	glfwSwapBuffers(window);
	glfwPollEvents();
}

static void menuObjectRender(float dt, int indexOfObject)
{ // Меняем спрайты для анимации объектов
	switch (menuObjects[indexOfObject].type)
	{
		case MenuObjectType_Military:
			menuMilitaryRender(dt, indexOfObject);
			break;
	}

	drawRotateTexture(int(menuObjects[indexOfObject].spriteX), int(menuObjects[indexOfObject].spriteY), menuObjects[indexOfObject].width, menuObjects[indexOfObject].height, menuObjects[indexOfObject].sprite, menuObjects[indexOfObject].directionAngle);
}

static void menuMilitaryRender(float dt, int indexOfObject)
{
	switch (menuObjects[indexOfObject].action)
	{
		case MenuMilitaryActions_Idle:
			menuObjects[indexOfObject].sprite = textureMenuMilitaryIdle;
			break;
		case MenuMilitaryActions_Run:
			changeMenuFrame(dt, indexOfObject, MenuMilitaryActions_Idle, textureMenuMilitaryRun, kNumberOfFramesMilitaryRun, kMilitaryRunAnimationSpeed);
			break;
		case MenuMilitaryActions_PressTheButton:
			if (changeMenuFrame(dt, indexOfObject, MenuMilitaryActions_Idle, textureMenuMilitaryPressTheButton, kNumberOfFramesMilitaryPressTheButton, kMilitaryPressTheButtonAnimationSpeed))
			{
				militaryPressTheButton = true;
				buttonPressed = false;
			}
			break;
	}
}

static bool changeMenuFrame(float dt, int indexOfObject, int idleAction, GLuint *texture, const int numberOfFrames, const int animationSpeed)
{
	if (menuMilitary.currentFrame >= 0 && menuMilitary.currentFrame < numberOfFrames)
	{
		menuObjects[indexOfObject].sprite = texture[int(menuMilitary.currentFrame)];
		menuMilitary.currentFrame += dt * animationSpeed;
	}
	else
	{
		menuMilitary.currentFrame = 0.0f;
		menuObjects[indexOfObject].sprite = texture[int(menuMilitary.currentFrame)];
		menuObjects[indexOfObject].action = idleAction;
		return true;
	}
	return false;
}

static void menuUpdate(float dt)
{
	for (int indexOfObject = 0; indexOfObject < NumberOfObjectsInMenu; indexOfObject++)
	{
		switch (menuObjects[indexOfObject].type)
		{
			case MenuObjectType_Military:
				menuMilitaryUpdate(dt, indexOfObject);
				break;
			case MenuObjectType_ButtonStartGame:
			case MenuObjectType_ButtonOptions:
			case MenuObjectType_ButtonAuthors:
			case MenuObjectType_ButtonExit:
				setButtonSprite(indexOfObject);
				break;
			case MenuObjectType_MilitaryButtonStartGame:
			case MenuObjectType_MilitaryButtonOptions:
			case MenuObjectType_MilitaryButtonAuthors:
			case MenuObjectType_MilitaryButtonExit:
				setMilitaryButtonSprite(indexOfObject);
				break;
		}
	}
}

static void menuMilitaryUpdate(float dt, int indexOfObject)
{
	int activeButtonY = moveMenuMilitary(dt, indexOfObject);

	double unitDirectionAngle = menuObjects[indexOfObject].directionAngle;
	float turningAngle = dt * kMenuMilitaryTurnSpeed;
	switch (menuMilitary.direction)
	{
		case Direction_Right:
			menuObjects[indexOfObject].directionAngle = calculateDirectionAngle(unitDirectionAngle, turningAngle, 0);
			break;
		case Direction_Up:
			menuObjects[indexOfObject].directionAngle = calculateDirectionAngle(unitDirectionAngle, turningAngle, 90);
			break;
		case Direction_Left:
			menuObjects[indexOfObject].directionAngle = calculateDirectionAngle(unitDirectionAngle, turningAngle, 180);
			break;
		case Direction_Down:
			menuObjects[indexOfObject].directionAngle = calculateDirectionAngle(unitDirectionAngle, turningAngle, 270);
			break;
	}

	if (menuObjects[indexOfObject].action == MenuMilitaryActions_Idle ||
		menuObjects[indexOfObject].action == MenuMilitaryActions_Run)
	{
		if (menuMilitary.ySpeed != 0)
		{
			changeMenuObjectAction(indexOfObject, MenuMilitaryActions_Run);
		}
		else
		{
			changeMenuObjectAction(indexOfObject, MenuMilitaryActions_Idle);
		}
	}

	if (buttonPressed && int(menuMilitary.y) == activeButtonY)
	{
		menuMilitary.ySpeed = 0.0f;
		changeMenuObjectAction(indexOfObject, MenuMilitaryActions_PressTheButton);
	}

	setMenuMilitarySpriteSize(indexOfObject);
}

static int moveMenuMilitary(float dt, int indexOfObject)
{
	int activeButtonY = int(menuObjects[MenuObjectType_ButtonStartGame].spriteY);
	for (int buttonType = MenuObjectType_ButtonStartGame; buttonType <= MenuObjectType_ButtonExit; buttonType++)
	{
		if (menuObjects[buttonType].action == MenuItemActions_Active)
		{
			activeButtonY = int(menuObjects[buttonType].spriteY);
		}
	}

	if (activeButtonY > int(menuMilitary.y + kMilitaryRangeOfButton))
	{
		menuMilitary.direction = Direction_Down;
		if (menuObjects[indexOfObject].directionAngle == 270.0)
		{
			menuMilitary.ySpeed = kMenuMilitarySpeed;
		}
	}
	else if (activeButtonY < int(menuMilitary.y - kMilitaryRangeOfButton))
	{
		menuMilitary.direction = Direction_Up;
		if (menuObjects[indexOfObject].directionAngle == 90.0)
		{
			menuMilitary.ySpeed = -kMenuMilitarySpeed;
		}
	}
	else
	{
		menuMilitary.y = float(activeButtonY);
		menuObjects[indexOfObject].spriteY = float(activeButtonY - kDistanceMilitaryButtonY);
		menuMilitary.ySpeed = 0.0f;
		menuMilitary.direction = Direction_Left;
		if (menuObjects[indexOfObject].directionAngle == 180.0 && buttonPressed)
		{
			menuObjects[indexOfObject].action = MenuMilitaryActions_PressTheButton;
		}
	}

	militaryPositionUpdate(dt, indexOfObject);

	return activeButtonY;
}

static void militaryPositionUpdate(float dt, int indexOfObject)
{
	int oldIntY = int(menuMilitary.y);
	float newY = menuMilitary.y + menuMilitary.ySpeed * dt;
	int newIntY = int(newY);

	if (oldIntY != newIntY)
	{
		menuMilitary.y = newY;
		menuObjects[indexOfObject].spriteY = newY - kDistanceMilitaryButtonY;
	}
}

static void changeMenuObjectAction(int indexOfObject, int action)
{
	if (menuObjects[indexOfObject].action != action)
	{
		menuObjects[indexOfObject].action = action;
		menuMilitary.currentFrame = 0.0f;
	}
}

static void setMenuMilitarySpriteSize(int indexOfObject)
{
	switch (menuObjects[indexOfObject].action)
	{
		case MenuMilitaryActions_Idle:
			menuObjects[indexOfObject].width = kMenuMilitaryPressTheButtonWidth;
			menuObjects[indexOfObject].height = kMenuMilitaryPressTheButtonHeight;
			break;
		case MenuMilitaryActions_Run:
			menuObjects[indexOfObject].width = kMenuMilitaryRunWidth;
			menuObjects[indexOfObject].height = kMenuMilitaryRunHeight;
			break;
		case MenuMilitaryActions_PressTheButton:
			menuObjects[indexOfObject].width = kMenuMilitaryPressTheButtonWidth;
			menuObjects[indexOfObject].height = kMenuMilitaryPressTheButtonHeight;
			break;
	}
}

bool isKeyPressed(const int virtualKeyCode)
{
	bool keyDown = isKeyDown(virtualKeyCode);
	if (keyDown)
	{
		lastPressedKeyCode = virtualKeyCode;
	}
	return keyDown;
}

static int getPressedMenuKeyCode()
{
	for (int i = 0; i < kNumberOfMenuButtons; i++)
	{
		if (isKeyDown(kMenuButtons[i]))
			return kMenuButtons[i];
	}
	return NULL;
}
static int lastItemState(const int numberOfItems)
{
	return numberOfItems - 1;
}
static int nextItemState(const int selectItemState)
{
	return selectItemState + 1;
}
static int previousItemState(const int selectItemState)
{
	return selectItemState - 1;
}
static int nextState(const int numberOfItems, const int selectItemState)
{
	return (selectItemState < lastItemState(numberOfItems)) ? nextItemState(selectItemState) : MenuItem_1;
}
static int previousState(const int numberOfItems, const int selectItemState)
{
	return (selectItemState > MenuItem_1) ? previousItemState(selectItemState) : lastItemState(numberOfItems);
}
static int stateWait(int numberOfItems, int selectItemState)
{
	return numberOfItems + selectItemState;
}
static int stateDisplay(const int numberOfItems, const int selectItemState)
{
	return selectItemState - numberOfItems - numberOfItems;
}

static int jumpToSelectItem(int numberOfItems, int selectItemState)
{
	int menu_state = selectItemState;
	int keyCode = getPressedMenuKeyCode();
	if (keyCode != lastPressedKeyCode)
	{
		lastPressedKeyCode = keyCode;
		selectItemState = selectItemState - numberOfItems;
		switch (keyCode)
		{
			case kMenuKeyDown:
				menu_state = nextState(numberOfItems, selectItemState);
				break;
			case kMenuKeyUp:
				menu_state = previousState(numberOfItems, selectItemState);
				break;
			case kMenuKeyEnter:
				menu_state = selectItemState + numberOfItems + numberOfItems;
				break;
			case kMenuKeyEsc:
				menu_state = kMenuExit;
				break;
			default:
				menu_state = stateWait(numberOfItems, selectItemState);
		}
	}
	return menu_state;
}

static void setButtonActive(MenuObjectType objectType)
{
	for (int buttonType = MenuObjectType_ButtonStartGame; buttonType <= MenuObjectType_ButtonExit; buttonType++)
	{
		if (menuObjects[buttonType].type == objectType)
		{
			menuObjects[buttonType].action = MenuItemActions_Active;
		}
		else
		{
			menuObjects[buttonType].action = MenuItemActions_Passive;
		}
	}
}

static void setMilitaryButtonActive(MenuObjectType buttonType)
{
	if (int(menuMilitary.currentFrame) >= kMilitaryPressTheButtonFrame)
	{
		for (int objectIndex = 0; objectIndex < NumberOfObjectsInMenu; objectIndex++)
		{
			if (menuObjects[objectIndex].type >= MenuObjectType_MilitaryButtonStartGame &&
				menuObjects[objectIndex].type <= MenuObjectType_MilitaryButtonExit)
			{
				if (menuObjects[objectIndex].type == buttonType)
				{
					menuObjects[objectIndex].action = MenuItemActions_Active;
				}
				else
				{
					menuObjects[objectIndex].action = MenuItemActions_Passive;
				}
			}
		}
	}
}

static void setMilitaryButtonPassive()
{
	for (int objectIndex = 0; objectIndex < NumberOfObjectsInMenu; objectIndex++)
	{
		if (menuObjects[objectIndex].type >= MenuObjectType_MilitaryButtonStartGame &&
			menuObjects[objectIndex].type <= MenuObjectType_MilitaryButtonExit)
		{
			menuObjects[objectIndex].action = MenuItemActions_Passive;
		}
	}
}