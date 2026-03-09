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
Scene* CreatePause();
Scene* CreateLvL1();
Scene* CreateLvL2();
Scene* CreateLvL3();
Scene* CreateGameOver();

// --- SINGLETON RUNTIME ---
class LevelRuntime {
private:
    GameObject* TimerWave = nullptr;
    bool isLevelInitialized = false;
    std::vector<EnnemiData> enemiesToSpawn;

    int currentLevelIndex = 0;
    std::vector<std::string> levelFiles = {
        "lvl1.txt",
        "lvl2.txt",
        "lvl3.txt"
    };
    Scene* currentActiveScene = nullptr;  // <-- AJOUT
    Scene* nextScene = nullptr;

    LevelRuntime() = default;

    void LoadEnemiesFromFile(const std::string& filename);
    void UpdateSpawning(float tempsEcoule, Scene* currentScene);
    

public:
    static LevelRuntime& Get() {
        static LevelRuntime instance;
        return instance;
    }

    LevelRuntime(const LevelRuntime&) = delete;
    void operator=(const LevelRuntime&) = delete;

    void UpdateLogic(Engine& engine);  // <-- MODIFIÉ (plus de paramètre targetLevel)
    void ResetLevel();
    bool IsLevelComplete(Scene* currentScene);
    void LoadNextLevel();
    void SetNextScene(Scene* scene) { nextScene = scene; }
    void SetCurrentActiveScene(Scene* scene) { currentActiveScene = scene; }  // <-- AJOUT
    void SetCurrentLevel(int index) { currentLevelIndex = index; }
    int GetCurrentLevel() { return currentLevelIndex; }
};