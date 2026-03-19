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
    struct SpawnLigne
    {
        int mapId;
        int Speed;
		std::pair<int, int> MinMaxTime;
        sf::Clock clock;
        int nextSpawnSec = 0;
        std::function<void()> CreateObstacle;
    };
    static std::vector<SpawnLigne> spawnLignes;
	spawnLignes.clear();
    for (int i = 0; i < map.size(); ++i)
    {
        switch (map[i])
        {
        case TileType::TRAINL:
        case TileType::TRAINR:
        {
            int mapId = i;
            int spd = 50;
            SpawnLigne sl;
			sl.mapId = mapId;
            sl.Speed = spd;
            sl.MinMaxTime = { 11,12 };
            sl.clock = sf::Clock();
            sl.nextSpawnSec = 0;
            sl.CreateObstacle = [i, lvl, spd]()
                {
                    GameObject* train = CreateTrain(i, map[i], spd);
                    train->Start();
                    lvl->AddGameObject(train, { sens(map[i]), i });
                };
            spawnLignes.push_back(sl);
            break;
        }
        case TileType::ROADL:
        case TileType::ROADR:
        {
            int mapId = i;
            int spd = rand() % 250 + 100;
            SpawnLigne sl;
            sl.mapId = mapId;
            sl.Speed = spd;
            sl.MinMaxTime = { 4,8 };
            sl.clock = sf::Clock();
            sl.nextSpawnSec = 0;
            sl.CreateObstacle = [i, lvl, spd]()
                {
                    GameObject* car = CreateCar(i, map[i], spd);
                    car->Start();
                    lvl->AddGameObject(car, { sens(map[i]), i });
                };
            spawnLignes.push_back(sl);
            break;
        }
        case TileType::WATERL:
        case TileType::WATERR:
        {
            int mapId = i;
            int spd = 300;
            SpawnLigne sl;
            sl.mapId = mapId;
            sl.Speed = spd;
            sl.MinMaxTime = { 4,5 };
            sl.clock = sf::Clock();
            sl.nextSpawnSec = 0;
            sl.CreateObstacle = [i, lvl, spd]()
                {
                    GameObject* boat = CreateBoat(i, map[i], spd);
                    boat->Start();
                    lvl->AddGameObject(boat, { sens(map[i]), i });
                };
            spawnLignes.push_back(sl);
            break;
        }
        }
    }
    static sf::Clock TrainClock;
    TrainClock.restart();
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
    InputManager::RegisterKeyPress("F12", []()
        {
            Event::SetEventTrue(1);
        });
    InputManager::RegisterKeyPress("F3", []()
        {
            Debug::ChangeDebug(3);
        });
    InputManager::RegisterKeyPress("F4", []()
        {
            Debug::ChangeDebug(4);
        });

    if (!eventsCreated)
    {

        // Gestion d'event a chaque boucle
        Event::CreateEvent(-1, [lvl]()
            {
                Conditions::Scrolling(lvl);
                if (Conditions::Collision(lvl) == CollideType::Dead)
                    Event::SetEventTrue(1);
                Conditions::Recalibrage(lvl);
                if (Conditions::testWin(lvl))
                    Event::SetEventTrue(1);
                
            });

        Event::CreateEvent(-2,[lvl]()
            {
				for (int i = 0; i < spawnLignes.size(); ++i)
                {
                    if(spawnLignes[i].CreateObstacle)
                    if (spawnLignes[i].clock.getElapsedTime().asSeconds() >= spawnLignes[i].nextSpawnSec)
                    {
						std::cout << "Spawn obstacle ligne " << spawnLignes[i].mapId << "sens" << TileTypeToString(map[spawnLignes[i].mapId]) << " en pos " << sens(map[spawnLignes[i].mapId]) << " " << spawnLignes[i].mapId <<  std::endl;
                        spawnLignes[i].CreateObstacle();
                        spawnLignes[i].clock.restart();
                        spawnLignes[i].nextSpawnSec = rand() % (spawnLignes[i].MinMaxTime.second-spawnLignes[i].MinMaxTime.first) + spawnLignes[i].MinMaxTime.first;
                    }
                }
			});

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








void InputHandler::MovePlayer(Scene* lvl)
{
    if (lvl == nullptr || lvl->GetPlayer() == nullptr)
    {
        std::cout << "ERREUR: lvl ou player est nullptr dans MovePlayer" << std::endl;
        return;
    }

    GameObject* player = lvl->GetPlayer();


    InputManager::RegisterKeyPress("Z", [player,lvl]()
        {
            if(engineRef->getSceneModule()->GetActiveScene() == lvl)
                Conditions::MoveUp(player,lvl);
        });
    InputManager::RegisterKeyPress("Up", [player, lvl]()
        {
            Conditions::MoveUp(player, lvl);
        });


    InputManager::RegisterKeyPress("S", [player, lvl]()
        {
            Conditions::MoveDown(player,lvl);
        });
    InputManager::RegisterKeyPress("Down", [player, lvl]()
        {
            Conditions::MoveDown(player, lvl);
        });


    InputManager::RegisterKeyPress("Q", [player, lvl]()
        {
            Conditions::MoveLeft(player, lvl);
        });
    InputManager::RegisterKeyPress("Left", [player, lvl]()
        {
            Conditions::MoveLeft(player, lvl);
        });


    InputManager::RegisterKeyPress("D", [player, lvl]()
        {
            Conditions::MoveRight(player, lvl);
        });
    InputManager::RegisterKeyPress("Right", [player, lvl]()
        {
            Conditions::MoveRight(player, lvl);
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
    InitScrollOffset();
    eventsCreated = false;
    debugF1 = false;
    debugF2 = false;
    debugF3 = false;
    debugF4 = false;

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


