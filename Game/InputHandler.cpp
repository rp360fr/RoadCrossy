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

sf::Vector2f InputHandler::scrolling(int x, int y)
{
        float screenX = (x - y) * tile_width / 2;
        float screenY = (x + y) * tile_height / 2;
        return sf::Vector2f(screenX, screenY);
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

    // Configuration des mouvements du joueur pour CE niveau spécifique
    MovePlayer(lvl);
    

    InputManager::RegisterKeyPress("F10", []()
        {
            Debug::ChangeDebug(10);
        });


    // Gestion des collisions

    if (!eventsCreated)
    {
        std::cout << "Creation des events de collision et IA" << std::endl;


        Event::CreateEvent(-1, [lvl]()
            {
                for (GameObject* obj : lvl->getLstObj())
                {
                    obj->getTransform().pos += { scrolling(0,1).x / 10000,scrolling(0,1).y / 10000 };
                }
            });
        // Gestion des collisions
        Event::CreateEvent(-2, []()
            {
                Scene* currentScene = engineRef->getSceneModule()->GetActiveScene();
                if (currentScene == nullptr || currentScene->getName() == "Pause" ||
                    currentScene->getName() == "Menu" || currentScene->getName() == "GameOver")
                    return;
                
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

    // Capturer le pointeur du joueur pour cette scène spécifique
    GameObject* player = lvl->GetPlayer();

    InputManager::RegisterKeyPress("Z", [player]()
        {
            if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
            {
                SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
                player->getTransform().pos += isometri(0,-1);
                sprite->setDirection(Direction::Up);
            }
        });

    InputManager::RegisterKeyPress("S", [player]()
        {
            if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
            {
                SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
				player->getTransform().pos += isometri(0, 1);
                sprite->setDirection(Direction::Down);
            }
        });

    InputManager::RegisterKeyPress("Q", [player]()
        {
            if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
            {
                SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
				player->getTransform().pos += isometri(-1, 0);
                sprite->setDirection(Direction::Left);
            }
        });

    InputManager::RegisterKeyPress("D", [player]()
        {
            if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
            {
                SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
				player->getTransform().pos += isometri(1, 0);
                sprite->setDirection(Direction::Right);
            }
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