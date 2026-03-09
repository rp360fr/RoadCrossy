#include "Engine.h"
#include "Scene.h"
#include "Projectiles.h"
#include "Player.h"
#include "Fond.h"
#include "LvlManager.h"
#include "InputHandler.h"
#include "Enemies.h"
#include <random>

static GameObject* TimerWave = nullptr;
static bool isLevelInitialized = false;

int main()
{
    srand(time(NULL));
    std::vector<Scene*>* lstScene = new std::vector<Scene*>;
    Engine engine({ 800, 600 }, "ShootEmUp");

    Scene* Menu = CreateMenuDepart(lstScene);
    Scene* LvL1 = CreateLvL1();
    Scene* LvL2 = CreateLvL2();
    Scene* LvL3 = CreateLvL2();
    Scene* Pause = CreatePause();
    Scene* GameOver = CreateGameOver();

    InputHandler::Initialize(&engine, lstScene, Pause);

    lstScene->push_back(Menu);
    lstScene->push_back(LvL1);
    lstScene->push_back(LvL2);
    lstScene->push_back(LvL3);
    lstScene->push_back(Pause);
    lstScene->push_back(GameOver);


    engine.getSceneModule()->SetActiveScene(Menu);
    InputHandler::SetupSceneInputs(Menu, "LaunchMenu");


    engine.Start();
    InputManager::Clear();

    for (Scene* scene : *lstScene) {
        delete scene;
    }
    delete lstScene;

    return 0;
}