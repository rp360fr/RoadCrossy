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
    Engine engine({ 800, 800 }, "ShootEmUp");

    Scene* Menu = CreateMenuDepart(lstScene);
    Scene* LvL = CreateGameLvL();
    Scene* GameOver = CreateGameOver();

    InputHandler::Initialize(&engine, lstScene);

    lstScene->push_back(Menu);
    lstScene->push_back(LvL);
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