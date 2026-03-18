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
    GameObject* fond = createFond("SpaceBackGround.png");
    GameObject* GameOverObject = new GameObject(sf::Vector2f( 0,0 ));
    AudioManager* ad = new AudioManager("GameOverSound.mp3");
    GameOverObject->AddComponent(ad);
    GameOver->SetLvLData(GameOverObject);
    Retry->setClickable(false);
    Quit->setClickable(false);
    GameOver->AddParamObject(fond);
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

TileType map[50] =
{
    GRASS,
    GRASS,
    GRASS,
    ROAD,
    ROAD,
    TRAIN,
    WATER,
    GRASS,
    ROAD,
    GRASS,
    GRASS,
    WATER,
    GRASS,
    ROAD,
    GRASS,
    GRASS,
    WATER,
    GRASS,
    ROAD,
    GRASS,
    GRASS,
    WATER,
    GRASS,
    ROAD,
    GRASS,
    TRAIN,
    WATER,
    GRASS,
    ROAD,
    GRASS,
    GRASS,
    WATER,
    GRASS,
    ROAD,
    GRASS,
    GRASS,
    WATER,
    GRASS,
    ROAD,
    TRAIN,
    GRASS,
    WATER,
    GRASS,
    ROAD,
    GRASS,
    GRASS,
    WATER,
    GRASS,
    ROAD,
    GRASS
};

void createMap(int length, int width, Scene* scene)
{
    int path = length / 2;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (map[i] == GRASS)
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
            }
            if (map[i] == GRASS)
            {
                path += (rand() % 3) - 1;
                if (path < 2) path = 2;
                if (path > length - 3) path = length - 3;
            }
            if (map[i] == ROAD)
            {
                GameObject* road = CreateRoad(j, i);
                scene->AddGroundObject(road);
            }

            if (map[i] == WATER)
            {
                GameObject* water = CreateWater(j, i);
                GameObject* hitbox = CreateWaterHitbox(j , i );

                scene->AddGroundObject(water);
                scene->AddGroundObject(hitbox);
            }
            if (map[i] == TRAIN)
            {
                GameObject* sol = CreateRails(j, i);
                scene->AddGroundObject(sol);
            }
        }
        if (map[i] == GRASS)
        {
            GameObject* gauche = CreateTree(0, i);
            scene->AddGameObject(gauche, { 0,i });
            GameObject* droite = CreateTree(14, i);
            scene->AddGameObject(droite, { 14,i });
        }

        if (map[i] == ROAD)
        {
            if (rand() % 2 == 0)
            {
                GameObject* voture = CreateCar(i, "Left");
                scene->AddGameObject(voture, { 0,i });
            }
            else
            {
                GameObject* voture = CreateCar(i, "Right");
                scene->AddGameObject(voture, { 14,i });
            }
        }

        if (map[i] == TRAIN)
        {
            if (rand() % 2 == 0)
            {
                GameObject* trin = CreateTrain(i, "Left");
                scene->AddGameObject(trin, { 0,i });
            }
            else
            {
                GameObject* trin = CreateTrain(i, "Right");
                scene->AddGameObject(trin, { 0,i });
            }
            
        }
        if (map[i] == WATER)
        {
            if (rand() % 2 == 0)
            {
                GameObject* Boat = CreateBoat(i, "Left");
                scene->AddGameObject(Boat, { 0,i });
            }
            else
            {
                GameObject* Boat = CreateBoat(i, "Right");
                scene->AddGameObject(Boat, { 14,i });
            }
        }
    }
}






Scene* CreateGameLvL()
{
    Scene* lvl1 = new Scene("LvL");
    GameObject* lvlObject = new GameObject(sf::Vector2f(0,0));
    GameObject* player = createPlayer(5,0);
    lvl1->AddGameObject(player, { 5,0 });
    lvl1->SetPlayer(player);
    createMap(15, 50, lvl1);
    lvl1->SetLvLData(lvlObject);
    return lvl1;
}
