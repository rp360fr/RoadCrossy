#include "LvlManager.h"
#include "InputHandler.h"


Scene* CreateMenuDepart(std::vector<Scene*>* lstScene)
{
    Scene* Launch = new Scene("LaunchMenu");
    GameObject* Play = createPlay();
    GameObject* Quit = createQuit();
    Play->setClickable(true);
    Quit->setClickable(true);
    Launch->AddGameObject(Play);
    Launch->AddGameObject(Quit);

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
    GameOver->AddGameObject(fond);
    GameOver->AddGameObject(Retry);
    GameOver->AddGameObject(Quit);
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
void createfloor(int x, int y, int length, int width, sf::Angle,Scene* scene) {
	for (int i = 0; i < width; i++)
     {
         for(int j = 0; j < length; j++)
         {
			 GameObject* floor = CreateGrass(x + j, y + i);
			 scene->AddGroundObject(floor); 
         }
     }
	
}


Scene* CreateGameLvL()
{
    Scene* lvl1 = new Scene("LvL");
    GameObject* lvlObject = new GameObject(sf::Vector2f(0,0));
    AudioManager* ad = new AudioManager("SpaceMainTheme.mp3");
    ad->SetLoop(true);
    lvlObject->AddComponent(ad);
    GameObject* player = createPlayer();
    
   /* createfloor(2, -1, 15, 1, sf::degrees(0), lvl1);*/
    GameObject* caillou = CreateRock(15,2);
    lvl1->AddGameObject(player);
    lvl1->AddGameObject(caillou);
    createfloor(2, 0, 15, 6, sf::degrees(0), lvl1);
    lvl1->SetPlayer(player);
    lvl1->SetLvLData(lvlObject);
    return lvl1;
}
