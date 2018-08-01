#pragma once

/////////////////////////////////////
// Константы
enum GameObjectType
{
	GameObjectType_Tile,

	GameObjectType_Wall,
	GameObjectType_Glass,
	GameObjectType_Table,
	GameObjectType_Chair,
	GameObjectType_Bin,
	GameObjectType_Generator0,
	GameObjectType_Generator2,
	GameObjectType_Arc,
	GameObjectType_Danger,
	GameObjectType_Reactor,
	GameObjectType_Sewerage,
	GameObjectType_Computer0,
	GameObjectType_Computer1,
	GameObjectType_DoorFell,
	GameObjectType_DoorOpened,
	GameObjectType_Door,
	GameObjectType_Corpse,
	GameObjectType_Aquarium,

	GameObjectType_Military,
	GameObjectType_Zombie,

	GameObjectType_Bullet,

	GameObjectType_GameOver,

	GameObjectType_None
};

enum GameObjectLayerType
{
	GameObjectLayerType_Background,
	GameObjectLayerType_Objects,
	GameObjectLayerType_Military,
	GameObjectLayerType_Units,
	GameObjectLayerType_Walls,
	GameObjectLayerType_GameOver,

	NumberOfGameObjectLayers
};