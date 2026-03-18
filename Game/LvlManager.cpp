#include "LvlManager.h"
#include "InputHandler.h"


Scene* CreateMenuDepart(std::vector<Scene*>* lstScene)
{
    Scene* Launch = new Scene("LaunchMenu");
    GameObject* Play = createPlay();
    GameObject* Quit = createQuit();
    Play->setClickable(true);
    Quit->setClickable(true);
    Launch->AddParamObject(Play);
    Launch->AddParamObject(Quit);
    InputManager::RegisterClickableObject(Play, [lstScene,Play,Quit](GameObject* obj) {
        std::cout << "Play cliqué !" << std::endl;
        if (lstScene->size() > 1) {
            Scene* lvl1 = InputHandler::getThisScene(lstScene, "LvL");

            Engine* engine = InputHandler::GetEngine();
            if (engine != nullptr && lvl1 != nullptr)
            {
                engine->getSceneModule()->SetActiveScene(lvl1);
                InputHandler::SetupSceneInputs(lvl1, "LvL");
                lvl1->Start();
                Play->setClickable(false);
                Quit->setClickable(false);
            }
        }
        });

    InputManager::RegisterClickableObject(Quit, [](GameObject* obj) {
        std::cout << "Quit cliqué !" << std::endl;
        exit(0);
        });

    return Launch;
}




Scene* CreateGameOver()
{
    Scene* GameOver = new Scene("GameOver");
    GameObject* Retry = createRetry();
    GameObject* Quit = createQuit();
    GameObject* GameOverObject = new GameObject(sf::Vector2f( 0,0 ));
    AudioManager* ad = new AudioManager("GameOverSound.mp3");
    GameOverObject->AddComponent(ad);
    GameOver->SetLvLData(GameOverObject);
    Retry->setClickable(false);
    Quit->setClickable(false);
    GameOver->AddParamObject(Retry);
    GameOver->AddParamObject(Quit);
    InputManager::RegisterClickableObject(Retry, [Retry, Quit](GameObject* obj) {
        std::cout << "Retry cliqué !\n\n\n\n\n\n" << std::endl;
        if (InputHandler::GetScenes()->size() > 1) {
            Retry->setClickable(false);
            Engine* engine = InputHandler::GetEngine();
            if (engine != nullptr)
            {
                Retry->setClickable(false);
                Quit->setClickable(false);
                InputHandler::RestartGame();
            }
        }
        });

    InputManager::RegisterClickableObject(Quit, [](GameObject* obj) {
        std::cout << "Quit cliqué !" << std::endl;
        exit(0);
        });
    return GameOver;
}



void createMap(int length, int width, Scene* scene)
{
    int path = length / 2;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (map[i] == TileType::GRASS)
            {
                GameObject* grass = CreateGrass(j, i);
                scene->AddGroundObject(grass);
                if ((j < path || j > path + 1) && i != 0)
                {
                    int r = rand() % 5;
                    if (r == 0)
                    {
                        GameObject* tree = CreateTree(j, i);
                        scene->AddGameObject(tree, { j, i });
                    }
                    else if (r == 1)
                    {
                        GameObject* rock = CreateRock(j, i);
                        scene->AddGameObject(rock, { j, i });
                    }
                }
                path += (rand() % 3) - 1;
                if (path < 2) path = 2;
                if (path > length - 3) path = length - 3;
            }

            else if (map[i] == TileType::ROAD)
            {
                GameObject* road = CreateRoad(j, i);
                scene->AddGroundObject(road);
            }

            else if (map[i] == TileType::WATER)
            {
                GameObject* water = CreateWater(j, i);
                GameObject* hitbox = CreateWaterHitbox(j , i );

                scene->AddGroundObject(water);
                scene->AddGroundObject(hitbox);
            }

            else if (map[i] == TileType::TRAIN)
            {
				std::cout << i << std::endl;
                GameObject* sol = CreateRails(j, i);
                scene->AddGroundObject(sol);
            }
        }



        if (map[i] == TileType::GRASS)
        {
            GameObject* gauche = CreateTree(0, i);
            scene->AddGameObject(gauche, { 0,i });
            GameObject* droite = CreateTree(14, i);
            scene->AddGameObject(droite, { 14,i });
        }

        if (map[i] == TileType::ROAD)
        {
            if (rand() % 2 == 0)
            {
				map[i] = TileType::ROADL;
            }
            else
            {
				map[i] = TileType::ROADR;
            }
        }

        if (map[i] == TileType::TRAIN)
        {
            if (rand() % 2 == 0)
            {
				map[i] = TileType::TRAINL;
            }
            else
            {
				map[i] = TileType::TRAINR;
            }
            
        }
        if (map[i] == TileType::WATER)
        {
            if (rand() % 2 == 0)
            {
				map[i] = TileType::WATERL;
            }
            else
            {
				map[i] = TileType::WATERR;
            }
        }
    }
}






Scene* CreateGameLvL()
{
	map = CreateMapTab();
    Scene* lvl1 = new Scene("LvL");
    GameObject* lvlObject = new GameObject(sf::Vector2f(0,0));
    GameObject* player = createPlayer(5,0);
    lvl1->AddGameObject(player, { 5,0 });
    lvl1->SetPlayer(player);
    createMap(15, 50, lvl1);
    lvl1->SetLvLData(lvlObject);
    return lvl1;
}
