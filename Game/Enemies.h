#pragma once
#include "Engine.h"
#include "Scene.h"
#include "Projectiles.h"
#include <fstream>

#include <sstream>



struct EnnemiData {
    int wave;
    int type;
    int spanwx;
};

extern std::vector<EnnemiData> enemiesToSpawn;
GameObject* CreateEnemiesType2();
GameObject* CreateEnemiesType1();
GameObject* CreateEnemiesMine();

void SpawnEnemies(int type, float spawnx, Scene* scene);
void BotAi(GameObject* Bot, Scene* LvL);