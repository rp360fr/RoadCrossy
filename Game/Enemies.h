#pragma once
#include "Engine.h"
#include "Scene.h"
#include <fstream>
#include <sstream>



struct EnnemiData {
    int wave;
    int type;
    int spanwx;
};
const float tile_width = 64;
const float tile_height = 64;
extern std::vector<EnnemiData> enemiesToSpawn;
GameObject* CreateGrass(int x, int y);
GameObject* CreateTree(int x, int y);
GameObject* CreateRock(int x,int y);
GameObject* CreateWater(int x, int y);
GameObject* CreateWaterHitbox(int x, int y);
GameObject* CreateBoat(int x, int y, std::string sens);
GameObject* CreateCar(int y,std::string sens);
GameObject* CreateEnemiesType2();
GameObject* CreateEnemiesType1();
GameObject* CreateEnemiesMine();

void SpawnEnemies(int type, float spawnx, Scene* scene);
void BotAi(GameObject* Bot, Scene* LvL);

