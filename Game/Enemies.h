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
GameObject* CreateGrass(sf::Vector2f vector);
GameObject* CreateTree(sf::Vector2f vector);
GameObject* CreateRock(sf::Vector2f vector,sf::Angle angle);
GameObject* CreateRiver(sf::Vector2f vector);
GameObject* CreateBoat(sf::Vector2f vector);
GameObject* CreateCar(sf::Vector2f vector);
GameObject* CreateEnemiesType2();
GameObject* CreateEnemiesType1();
GameObject* CreateEnemiesMine();

void SpawnEnemies(int type, float spawnx, Scene* scene);
void BotAi(GameObject* Bot, Scene* LvL);

