#pragma once
#include "Engine.h"
#include "Scene.h"
#include "Extern.h"
#include "Color.h"
#include <fstream>
#include <sstream>



GameObject* CreateGrass(int x, int y);
GameObject* CreateRoad(int x, int y);
GameObject* CreateTree(int x, int y);
GameObject* CreateRock(int x,int y);
GameObject* CreateWater(int x, int y);
GameObject* CreateWaterHitbox(int x, int y);
GameObject* CreateBoat(int y, TileType,int speed);
GameObject* CreateCar(int y, TileType,int speed);
GameObject* CreateTrain(int y, TileType,int speed);
GameObject* CreateRails(int x, int y);
