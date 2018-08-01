#pragma once

/////////////////////////////////////
// Подключаемые библиотеки
#include "items.h"
#include "mapObjects.h"


/////////////////////////////////////
// Текстура Background
const char kFolderBackground[] = "Textures/Map/Background/";
const int kNumberOfSpritesBackground = NumberOfBackground;


/////////////////////////////////////
// Текстура GameOver
const char kFolderTextureYouAreDied[] = "Textures/Menu/";
const char kTextureYouAreDied[] = "You are died.png";
const float kTextureYouAreDiedWidthCells = 40.2272f;
const float kTextureYouAreDiedHeightCells = 17.2272f;
const int kNumberOfFramesYouAreDied = 100;
const int kYouAreDiedAnimationSpeed = 80;


/////////////////////////////////////
// Текстуры Стен
const char kFolderWhiteWall[] = "Textures/Map/Walls/White wall/";
const int kNumberOfSpritesWhiteWall = NumberOfWalls;

const char kFolderGlassWall[] = "Textures/Map/Walls/Glass wall/";
const int kNumberOfSpritesGlassWall = NumberOfGlassWalls;


/////////////////////////////////////
// Текстуры Вещей
const char kFolderItems[] = "Textures/Map/Items/";
const int kNumberOfSpritesItems = NumberOfItems;


/////////////////////////////////////
// Текстуры Аквариума
const char kFolderAquariumIdle[] = "Textures/Map/Aquarium/Idle/";
const int kNumberOfFramesAquariumIdle = 6;

const char kFolderAquariumBreak[] = "Textures/Map/Aquarium/Break/";
const int kNumberOfFramesAquariumBreak = 9;


/////////////////////////////////////
// Текстуры Военного
const char kFolderMilitaryAK47Idle[] = "Textures/Military/AK47/Idle/";
const int kNumberOfFramesMilitaryAK47Idle = 50;
const int kMilitaryAK47IdleWidth = 225;
const int kMilitaryAK47IdleHeight = 115;
const int kMilitaryAK47IdleAnimationSpeed = 30;

const char kFolderMilitaryAK47RunningWithAiming[] = "Textures/Military/AK47/Running with aiming/";
const int kNumberOfFramesMilitaryAK47RunningWithAiming = 26;
const int kMilitaryAK47RunningWithAimingWidth = 320;
const int kMilitaryAK47RunningWithAimingHeight = 141;
const int kMilitaryAK47RunningWithAimingAnimationSpeed = 20;

const char kFolderMilitaryAK47Shoot[] = "Textures/Military/AK47/Shoot/";
const int kNumberOfFramesMilitaryAK47Shoot = 15;
const int kMilitaryAK47ShootWidth = 218;
const int kMilitaryAK47ShootHeight = 110;
const int kMilitaryAK47ShootAnimationSpeed = 20;

const char kFolderMilitaryAK47Knife[] = "Textures/Military/AK47/Knife/";
const int kNumberOfFramesMilitaryAK47Knife = 49;
const int kMilitaryAK47KnifeWidth = 224;
const int kMilitaryAK47KnifeHeight = 188;
const int kMilitaryAK47KnifeAnimationSpeed = 40;

const char kFolderMilitaryAK47SmallDamage[] = "Textures/Military/AK47/Small damage/";
const int kNumberOfFramesMilitaryAK47SmallDamage = 60;
const int kMilitaryAK47SmallDamageWidth = 249;
const int kMilitaryAK47SmallDamageHeight = 155;
const int kMilitaryAK47SmallDamageAnimationSpeed = 20;

const char kFolderMilitaryAK47BigDamage[] = "Textures/Military/AK47/Big damage/";
const int kNumberOfFramesMilitaryAK47BigDamage = 100;
const int kMilitaryAK47BigDamageWidth = 352;
const int kMilitaryAK47BigDamageHeight = 178;
const int kMilitaryAK47BigDamageAnimationSpeed = 20;

const char kFolderMilitaryAK47Death[] = "Textures/Military/AK47/Death/";
const int kNumberOfFramesMilitaryAK47Death = 50;
const int kMilitaryAK47DeathWidth = 300;
const int kMilitaryAK47DeathHeight = 300;
const int kMilitaryAK47DeathAnimationSpeed = 20;


/////////////////////////////////////
// Текстуры Зомби
const char kFolderZombieIdle[] = "Textures/Zombie/Idle/";
const int kNumberOfFramesZombieIdle = 250;
const int kZombieIdleWidth = 124;
const int kZombieIdleHeight = 150;
const int kZombieIdleAnimationSpeed = 30;

const char kFolderZombieWalk[] = "Textures/Zombie/Walk/";
const int kNumberOfFramesZombieWalk = 40;
const int kZombieWalkWidth = 166;
const int kZombieWalkHeight = 124;
const int kZombieWalkAnimationSpeed = 20;

const char kFolderZombieAttac0[] = "Textures/Zombie/Attac0/";
const int kNumberOfFramesZombieAttac0 = 40;
const int kZombieAttac0Frame = 14;
const int kZombieAttac0Width = 231;
const int kZombieAttac0Height = 155;
const int kZombieAttac0AnimationSpeed = 40;

const char kFolderZombieAttac1[] = "Textures/Zombie/Attac1/";
const int kNumberOfFramesZombieAttac1 = 40;
const int kZombieAttac1Width = 262;
const int kZombieAttac1Height = 226;
const int kZombieAttac1AnimationSpeed = 40;

const char kFolderZombieAttac2[] = "Textures/Zombie/Attac2/";
const int kNumberOfFramesZombieAttac2 = 40;
const int kZombieAttac2Width = 328;
const int kZombieAttac2Height = 173;
const int kZombieAttac2AnimationSpeed = 40;

const char kFolderZombieAttac3[] = "Textures/Zombie/Attac3/";
const int kNumberOfFramesZombieAttac3 = 40;
const int kZombieAttac3Width = 214;
const int kZombieAttac3Height = 158;
const int kZombieAttac3AnimationSpeed = 40;