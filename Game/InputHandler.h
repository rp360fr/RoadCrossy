#pragma once
#include "Engine.h"
#include "Scene.h"
#include "QTE.h"
#include "Player.h"
#include "Menu.h"
#include "Enemies.h"
#include "LvlManager.h"
#include "Conditions.h"

class InputHandler
{
private:
    static void SetupMenuInputs(Scene* menu);
    static void SetupLvLInputs(Scene* lvl);
    static void SetupQTEInputs(Scene* qte);
    static bool eventsCreated;
    static Engine* engineRef;
    static std::vector<Scene*>* scenesRef;
    static ArrowMiniGame* qteGame;

public:
    static void Initialize(Engine* engine, std::vector<Scene*>* scenes);

    static void SetupSceneInputs(Scene* scene, std::string sceneName);
    static void ClearSceneInputs();
    static void RestartGame();
    static void MovePlayer(Scene* scene);
  
    static Scene* getThisScene(std::vector<Scene*>* lstScene, std::string name);
    static Engine* GetEngine() { return engineRef; }
    static std::vector<Scene*>* GetScenes() { return scenesRef; }
    static void SetScenes(std::vector<Scene*>* s) { scenesRef = s; }

  

};
