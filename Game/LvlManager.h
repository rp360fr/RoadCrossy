#pragma once
#include "Engine.h"
#include "Scene.h"
#include "Player.h"
#include "Fond.h"
#include "Projectiles.h"
#include "Menu.h"
#include "Enemies.h"
#include <vector>
#include "PowerUp.h"


Scene* CreateMenuDepart(std::vector<Scene*>* lstScene);
Scene* CreateGameLvL();
Scene* CreateGameOver();

GameObject* createfloor(int x, int y,  int length, int width,sf::Angle, Scene* scene);
