#pragma once
#include "Engine.h"
#include "Scene.h"

#include "Player.h"
#include "Menu.h"
#include "Enemies.h"
#include "LvlManager.h"
#include "Extern.h"

class Conditions
{
public:
	static void MoveUp(GameObject* player, std::vector<GameObject*>& lstObj);
	static void MoveDown(GameObject* player, std::vector<GameObject*>& lstObj);
	static void MoveLeft(GameObject* player, std::vector<GameObject*>& lstObj);
	static void MoveRight(GameObject* player, std::vector<GameObject*>& lstObj);
	static void Scrolling(Scene* lvl);
	static bool testWin(Scene* lvl);
	static bool Collision(Scene* lvl);
	static void Recalibrage(Scene* lvl);
	static void Replace(GameObject* obj,std::string sens);
	static void Clean(std::vector<GameObject*>& tab,GameObject* obj,std::string sens);
};
