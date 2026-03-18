#pragma once
#include "Engine.h"
#include "Scene.h"
#include "Player.h"
#include "Fond.h"

#include "Menu.h"
#include "Enemies.h"
#include <vector>

enum TileType
{
    GRASS,
    ROAD,
    WATER,
    TRAIN
};

Scene* CreateMenuDepart(std::vector<Scene*>* lstScene);
Scene* CreateGameLvL();
Scene* CreateGameOver();



//void createfloor(int x, int y,  int length, int width,sf::Angle, Scene* scene);
