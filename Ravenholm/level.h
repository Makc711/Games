#pragma once

/////////////////////////////////////
// Подключаемые библиотеки
#include "openglLib.h"


/////////////////////////////////////
// Константы
const int kLevelRows = 32;
const int kLevelColumns = 62;
const int kPixelsPerCell = kScreenWidth / kLevelColumns;
const int kPixelsOnTop = kScreenHeight - kLevelRows * kPixelsPerCell;
const int kPixelsOnLeft = (kScreenWidth - kLevelColumns * kPixelsPerCell) / 2;

const char CellSymbol_Empty =		' ';

const char CellSymbol_Tile0 =		'+';

const char CellSymbol_Wall0 =		'='; // ═
const char CellSymbol_Wall1 =		'|'; // ║
const char CellSymbol_Wall2 =		'Г'; // ╔
const char CellSymbol_Wall3 =		'L'; // ╚
const char CellSymbol_Wall4 =		'J'; // ╝
const char CellSymbol_Wall5 =		'¬'; // ╗
const char CellSymbol_Wall6 =		'П'; // ╖
const char CellSymbol_Wall7 =		'['; // ╘
const char CellSymbol_Wall8 =		'U'; // ╜
const char CellSymbol_Wall9 =		']'; // ╛
const char CellSymbol_Wall10 =		'_'; // ╩
const char CellSymbol_Wall11 =		'{'; // ╣
const char CellSymbol_Wall12 =		'T'; // ╦
const char CellSymbol_Wall13 =		'}'; // ╠
const char CellSymbol_Wall14 =		'#'; // ╬
const char CellSymbol_Glass0 =		'/'; // │
const char CellSymbol_Glass1 =		'-'; // ─

const char CellSymbol_Table0 =		't';
const char CellSymbol_Chair =		'c';
const char CellSymbol_Bin =			'b';
const char CellSymbol_Generator =	'g';
const char CellSymbol_Arc =			'a';
const char CellSymbol_Danger0 =		'd';
const char CellSymbol_Reactor2 =	'r';
const char CellSymbol_Generator2 =	'h';
const char CellSymbol_Reactor0 =	'f';
const char CellSymbol_Reactor1 =	'v';
const char CellSymbol_Sewerage0 =	's';
const char CellSymbol_Sewerage1 =	'x';
const char CellSymbol_Puddle0 =		'p';
const char CellSymbol_Puddle1 =		'q';
const char CellSymbol_Puddle2 =		'o';
const char CellSymbol_Computer0 =	'k';
const char CellSymbol_Computer1 =	'm';
const char CellSymbol_DoorFell =	'e';
const char CellSymbol_DoorOpened =	'i';
const char CellSymbol_Door0 =		'y';

const char CellSymbol_Corpse0 =		'X';
const char CellSymbol_Corpse1 =		'D';
const char CellSymbol_Corpse2 =		'F';

const char CellSymbol_Aquarium =	'W';

const char CellSymbol_Military =	'M';
const char CellSymbol_Zombie =		'Z';

const char kLevelData0[kLevelRows][kLevelColumns + 1] =
{
	"T============================================================¬",
	"U                         W          F                       |",
	"y                                                  Z         |",
	"   +     +     +     +     +     +     +     +     +     +  +|",
	"                                                             |",
	"y                                                            |",
	"     M                                                       |",
	"                                                             |",
	"П                                                        x   |",
	"|  +     +     +     +     +     +     +     +     +     +  +|",
	"#==]e    i[=====¬                                            |",
	"|m         F    |  D                               p         |",
	"|               |                                            |",
	"|               |                           Z            f   |",
	"|               U Z                                          |",
	"|  +     +     +/    +     +     +     +     +     +     +  +|",
	"|               /                                            |",
	"|    Z X        /                                q           |",
	"|               /                                            |",
	"|            k  /                                        v   |",
	"|               /               Z                            |",
	"|  +     +     +/    +     +     +     +     +     +     +  +|",
	"|               /           X                                |",
	"|b              /                                   o        |",
	"|               /                                            |",
	"|t              /   Z                                    s   |",
	"|               /                                 Z          |",
	"|  +     +     +П   g+     +     + r   +h    +     +     +  +|",
	"|   c           |                                            |",
	"|               |           a d                              |",
	"|  +     +     +|    +     +     +     +     +     +     +  +|",
	"L===============_============================================J",
};

/////////////////////////////////////
// Данные Военного
const int kMilitaryHealth = 10;
const int kMilitaryAmmunition = 20;
const int kMilitarySpriteSize = 50;
const int kMilitaryCellSize = 2;
const int kMilitaryPixelsSize = kMilitaryCellSize * kPixelsPerCell;
const float kMilitarySpeedCellsPerSecond = 10.0f;
const float kMilitarySpeed = kMilitarySpeedCellsPerSecond * kPixelsPerCell;
const float kMilitaryTurnSpeed = 400.0f;
const float kMilitaryScratchingDistanceCells = 0.5f;
const float kMilitaryScratchingDistance = kMilitaryScratchingDistanceCells * kPixelsPerCell;
const float kMilitaryScratchingTime = 0.5f;
const float kMilitaryFireCooldownTime = 0.5f;
const int kDamageFromMilitaryScratch = 1;
const int kHardDamage = 2;

/////////////////////////////////////
// Данные состояния военного
const int kHealthWidthPixels = int(1.0f * kPixelsPerCell);
const int kHealthHeightPixels = int(1.0f * kPixelsPerCell);
const int kPixelsBetweenHealth = int(0.1f * kPixelsPerCell);
const int kHealthLeftDistance = int(0.5f * kPixelsPerCell);
const int kHealthTopDistance = int(float(kPixelsOnTop) / 3 - float(kHealthHeightPixels) / 2 - 3);
const int kAmmunitionWidthPixels = int(0.7f * kPixelsPerCell);
const int kAmmunitionHeightPixels = int(1.0f * kPixelsPerCell);
const int kPixelsBetweenAmmunition = int(0.1f * kPixelsPerCell);
const int kAmmunitionLeftDistance = int(0.5f * kPixelsPerCell);
const int kAmmunitionTopDistance = int(float(kPixelsOnTop) * 2 / 3 - float(kAmmunitionHeightPixels) / 2 + 3);

/////////////////////////////////////
// Данные Зомби
const int kZombieHealth = 1;
const int kZombieSpriteSize = 40;
const int kZombieCellSize = 2;
const int kZombiePixelsSize = kZombieCellSize * kPixelsPerCell;
const float kZombieSpeedCellsPerSecond = 3.0f;
const float kZombieSpeed = kZombieSpeedCellsPerSecond * kPixelsPerCell;
const float kZombieTurnSpeed = 400.0f;
const float kZombieAIAnalizeTime = 1.5f;
const float kZombieScratchingDistanceCells = 2.0f;
const float kZombieScratchingDistance = kZombieScratchingDistanceCells * kPixelsPerCell;
const float kZombieScratchingTime = 0.5f;
const int kDamageFromZombieScratch = 1;

/////////////////////////////////////
// Данные пуль
const float kPistolBulletSpeedCellsPerSecond = 20.0f;
const float kPistolBulletSpeed = kPistolBulletSpeedCellsPerSecond * kPixelsPerCell;
const int kDamageFromPistolBullet = 1;
const int kBulletDiameterPixels = int(0.1818f * kPixelsPerCell);

/////////////////////////////////////
// Данные Аквариума
const int kAquariumWidthPixels = int(5.0909f * kPixelsPerCell);
const int kAquariumHeightPixels = int(1.7272f * kPixelsPerCell);
const int kAquariumSpriteWidthPixels = int(7.0909f * kPixelsPerCell);
const int kAquariumSpriteHeightPixels = int(6.0909f * kPixelsPerCell);
const int kAquariumAnimationSpeed = 5;