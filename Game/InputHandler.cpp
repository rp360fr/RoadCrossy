// InputHandler.cpp
#include "InputHandler.h"
Engine* InputHandler::engineRef = nullptr;
std::vector<Scene*>* InputHandler::scenesRef = nullptr;
bool InputHandler::eventsCreated = false;

void InputHandler::Initialize(Engine* engine, std::vector<Scene*>* scenes)
{
    engineRef = engine;
    scenesRef = scenes;
    if (engineRef == nullptr)
        std::cout << " Erreur Engine " << std::endl;
    else if (scenesRef == nullptr)
        std::cout << " Erreur LstScene " << std::endl;
    else
        std::cout << "InputHandler initialise" << std::endl;
}




void InputHandler::SetupSceneInputs(Scene* scene, std::string sceneName)
{
    if (scene == nullptr)
    {
        std::cout << "ERREUR: scene est nullptr dans SetupSceneInputs" << std::endl;
        return;
    }
    ClearSceneInputs();
  

    if (sceneName == "LaunchMenu")
    {
        SetupMenuInputs(scene);
    }
    else if (sceneName == "LvL1" || sceneName == "LvL2" || sceneName == "LvL")
    {
        SetupLvLInputs(scene);
    }

    std::cout << "Inputs configures pour: " << sceneName << std::endl;
}

void InputHandler::ClearSceneInputs()
{
    InputManager::ClearKeyCallbacks();
    Event::ClearAllEvents();
    std::cout << "Tous les callbacks d'input ont ete nettoyes" << std::endl;
}

void InputHandler::SetupMenuInputs(Scene* menu)
{
    InputManager::RegisterKeyPress("Escape", []()
        {
            std::cout << "Quitter le jeu..." << std::endl;
            exit(0);
        });
}

void InputHandler::SetupLvLInputs(Scene* lvl)
{
    if (lvl == nullptr)
    {
        std::cout << "ERREUR: lvl est nullptr dans SetupLvLInputs" << std::endl;
        return;
    }

    // Configuration des mouvements du joueur
    MovePlayer(lvl);
    

    InputManager::RegisterKeyPress("F1", []()
        {
            Debug::ChangeDebug(1);
        });
    InputManager::RegisterKeyPress("F2", []()
        {
            Debug::ChangeDebug(2);
        });


    // Gestion des collisions

    if (!eventsCreated)
    {

        // Gestion d'event a chaque boucle
        Event::CreateEvent(-1, [lvl]()
            {
                Conditions::Scrolling(lvl);
                if (Conditions::testWin(lvl))
                    Event::SetEventTrue(1);
            });



        //Fin
        Event::CreateEvent(1, []()
            {
                Scene* GameOver = InputHandler::getThisScene(scenesRef, "GameOver");
                GameOver->getThisObjByText("Retry")->setClickable(true);
                GameOver->getThisObjByText("Quit")->setClickable(true);
                engineRef->getSceneModule()->SetActiveScene(GameOver);
                GameOver->Start();
                engineRef->setGameState(false);
            });

        eventsCreated = true;
    }
}

void InputHandler::TestDeath()
{
}







void InputHandler::MovePlayer(Scene* lvl)
{
    if (lvl == nullptr || lvl->GetPlayer() == nullptr)
    {
        std::cout << "ERREUR: lvl ou player est nullptr dans MovePlayer" << std::endl;
        return;
    }

    GameObject* player = lvl->GetPlayer();
    std::vector<GameObject*>& lstObj = lvl->getLayer2Obj();

    InputManager::RegisterKeyPress("Z", [player,&lstObj]()
        {
            Conditions::MoveUp(player, lstObj);
        });
    InputManager::RegisterKeyPress("Up", [player, &lstObj]()
        {
            Conditions::MoveUp(player, lstObj);
        });


    InputManager::RegisterKeyPress("S", [player,&lstObj]()
        {
            Conditions::MoveDown(player, lstObj);
        });
    InputManager::RegisterKeyPress("Down", [player, &lstObj]()
        {
            Conditions::MoveDown(player, lstObj);
        });


    InputManager::RegisterKeyPress("Q", [player, &lstObj]()
        {
            Conditions::MoveLeft(player, lstObj);
        });
    InputManager::RegisterKeyPress("Left", [player, &lstObj]()
        {
            Conditions::MoveLeft(player, lstObj);
        });


    InputManager::RegisterKeyPress("D", [player,&lstObj]()
        {
            Conditions::MoveRight(player, lstObj);
        });
    InputManager::RegisterKeyPress("Right", [player, &lstObj]()
        {
            Conditions::MoveRight(player, lstObj);
        });
}

Scene* InputHandler::getThisScene(std::vector<Scene*>* lstScene, std::string name)
{
    for (int i = 0; i < lstScene->size(); ++i)
    {
        Scene* search = (*lstScene)[i];
        if (search->getName() == name)
            return search;
    }
    return nullptr;
}



void InputHandler::RestartGame()
{
    std::cout << "=== RESTART DU JEU ===\n\n\n\n" << std::endl;
    engineRef->setGameState(false);

    // 1. Nettoyer les anciens callbacks
    InputManager::ClearKeyCallbacks();
    Event::ClearAllEvents();
    eventsCreated = false;

    // 2. Détruire et recréer les scènes
    for (Scene* scene : *scenesRef)
    {
        if (scene != nullptr)
        {
            scene->Destroy();
            delete scene;
        }
    }
    scenesRef->clear();

    Scene* Menu = CreateMenuDepart(scenesRef);
    Scene* LvL = CreateGameLvL();

    Scene* GameOver = CreateGameOver();

    scenesRef->push_back(Menu);
    scenesRef->push_back(LvL);
    scenesRef->push_back(GameOver);
    


    engineRef->getSceneModule()->SetActiveScene(Menu);
    InputHandler::SetupSceneInputs(Menu, "LaunchMenu");

    engineRef->setGameState(true);

    std::cout << "=== JEU REINITIALISE ===\n\n\n\n" << std::endl;
}