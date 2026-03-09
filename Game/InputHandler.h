#pragma once
#include "Engine.h"
#include "Scene.h"
#include "Projectiles.h"
#include "Player.h"
#include "Menu.h"
#include "Enemies.h"
#include "LvlManager.h"

class InputHandler
{
private:
    static void SetupMenuInputs(Scene* menu);
    static void SetupLvLInputs(Scene* lvl);
    static bool eventsCreated;
    static Scene* pauseScene;
    static Scene* tempPauseScene;
    static Engine* engineRef;
    static std::vector<Scene*>* scenesRef;

public:
    static void Initialize(Engine* engine, std::vector<Scene*>* scenes, Scene* pause);

    static void TestDeath();
    static void CollisionProjectiles();
    static void CollisionVaisseau();
    static void CollisionBonusMalus();
    static void SetupSceneInputs(Scene* scene, std::string sceneName);
    static void ClearSceneInputs();
    static void RestartGame();
    static void MovePlayer(Scene* scene);
    static Scene* getThisScene(std::vector<Scene*>* lstScene, std::string name);
    static Engine* GetEngine() { return engineRef; }
    static Scene* GetTempPauseScene() { return tempPauseScene; }
    static Scene* GetPauseScene() { return pauseScene; }
    static std::vector<Scene*>* GetScenes() { return scenesRef; }
    static void SetScenes(std::vector<Scene*>* s) { scenesRef = s; }
};