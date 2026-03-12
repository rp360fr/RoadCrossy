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


        Event::CreateEvent(-1, [lvl]()
            {
                if (debugF1)
                {
                    for (GameObject* obj : lvl->getGroundObj())
                    {
                        obj->getTransform().pos += { scrolling(0, 2).x / 1000, scrolling(0, 1).y / 1000 };
                    }
                    for (GameObject* obj : lvl->getLayer2Obj())
                    {
                        if(obj != nullptr)
                            obj->getTransform().pos += { scrolling(0, 2).x / 1000, scrolling(0, 1).y / 1000 };
                    }
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



bool moveElement(std::vector<GameObject*>& list, int posStart, int posFin)
{
    GameObject* elem = list[posStart];
    if (list[posFin] == nullptr)
    {
        list[posFin] = elem;
        list[posStart] = nullptr;
        Debug::DebugCout("pos joueur tab "+posFin,2);
        return true;
    }
    else
    {
        return false;
    }
    
}



bool InputHandler::ChangeLayer(std::vector<GameObject*>& obj,GameObject* player, char mv)
{
    int id = -1;
    bool test = false;
    for (int i = 0; i < obj.size(); i++)
    {
        if (obj[i] == player)
        {
            id = i;
            break;
        }
    }

    if (id == -1) return false;



    switch (mv)
    {
    case 'U': if(id+15 < 1500) test = moveElement(obj, id, id+15); break;
    case 'D': if (id - 15 >= 0) test = moveElement(obj, id, id-15); break;
    case 'R': if (id - 1 >= 0 ) test = moveElement(obj, id, id-1); break;
    case 'L': if (id + 1 < 1500) test = moveElement(obj, id, id+1); break;
    }
    return test;
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
    std::vector<GameObject*>& lstObj = lvl->getLayer2Obj();
    InputManager::RegisterKeyPress("Z", [player,&lstObj]()
        {
            if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
            {
                if (ChangeLayer(lstObj, player, 'U'))
                {
                    SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
                    player->getTransform().pos += calcMouvement(0, -1);
                    sprite->setDirection(Direction::Up);
                }
                
            }
        });

    InputManager::RegisterKeyPress("S", [player,&lstObj]()
        {
            if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
            {
                if (ChangeLayer(lstObj, player, 'D'))
                {
                    SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
                    player->getTransform().pos += calcMouvement(0, 1);
                    sprite->setDirection(Direction::Down);
                }
                
            }
        });

    InputManager::RegisterKeyPress("Q", [player,&lstObj]()
        {
            if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
            {
                if (ChangeLayer(lstObj, player, 'L'))
                {
                    SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
                    player->getTransform().pos += calcMouvement(-1, 0);
                    sprite->setDirection(Direction::Left);
                }
            }
        });

    InputManager::RegisterKeyPress("D", [player,&lstObj]()
        {
            if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
            {
                if (ChangeLayer(lstObj, player, 'R'))
                {
                    SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
                    player->getTransform().pos += calcMouvement(1, 0);
                    sprite->setDirection(Direction::Right);
                }
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

sf::Vector2f InputHandler::calcMouvement(int x, int y)
{
    float screenX = (x - y) * tile_width / 2;
    float screenY = (x + y) * tile_height / 4;
    return sf::Vector2f(screenX, screenY);
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