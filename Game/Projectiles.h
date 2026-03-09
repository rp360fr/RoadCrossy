#pragma once
#include "Engine.h"
#include "Scene.h"

GameObject* CreateProjectile(GameObject* player);

GameObject* CreateEProjectile(GameObject* ennemie, GameObject* Player);

GameObject* BossPhase1(GameObject* ennemie, GameObject* Player);
