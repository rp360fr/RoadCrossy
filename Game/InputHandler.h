#pragma once
#include "Engine.h"
#include "Scene.h"

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
    static Engine* engineRef;
    static std::vector<Scene*>* scenesRef;

public:
    static void Initialize(Engine* engine, std::vector<Scene*>* scenes);

    static void TestDeath();
    static void SetupSceneInputs(Scene* scene, std::string sceneName);
    static void ClearSceneInputs();
    static void RestartGame();
    static void MovePlayer(Scene* scene);
    static sf::Vector2f scrolling(int x, int y);
    static Scene* getThisScene(std::vector<Scene*>* lstScene, std::string name);
    static Engine* GetEngine() { return engineRef; }
    static bool ChangeLayer(std::vector<GameObject*>& obj,GameObject* player, char mv);
    static std::vector<Scene*>* GetScenes() { return scenesRef; }
    static void SetScenes(std::vector<Scene*>* s) { scenesRef = s; }
    static sf::Vector2f calcMouvement(int x, int y);
};