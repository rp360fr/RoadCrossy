#pragma once
#include "Engine.h"
#include "Scene.h"

#include "Player.h"
#include "Menu.h"
#include "Enemies.h"
#include "LvlManager.h"
#include "Extern.h"

enum class CollideType
{
	Dead,
	Block,
	Boat,
	Null
};


class Conditions
{
	
public:
	static sf::Vector2f scrollOffset;
	static void MoveUp(GameObject* player, Scene* lvl);
	static void MoveDown(GameObject* player, Scene* lvl);
	static void MoveLeft(GameObject* player, Scene* lvl);
	static void MoveRight(GameObject* player, Scene* lvl);
	static void Scrolling(Scene* lvl);
	static bool testWin(Scene* lvl);
	static void DelPlayer(Scene* lvl);
	static CollideType Collision(Scene* lvl);
	static GameObject* Collision(Scene* lvl,char D);
	static void Recalibrage(Scene* lvl);
	static void Replace(GameObject* obj,std::string sens);
};
