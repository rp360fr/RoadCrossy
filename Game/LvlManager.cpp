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
void createfloor(int x, int y, int length, int width, sf::Angle,Scene* scene) {
	for (int i = width; i > 0; i--)
     {
         for(int j = length; j > 0; j--)
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
    GameObject* player = createPlayer(0,0);
    lvl1->AddGameObject(player, { 0,0 });
   /* createfloor(2, -1, 15, 1, sf::degrees(0), lvl1);*/
    GameObject* caillou = CreateRock(8,2);
    GameObject* caillou2 = CreateRock(9, 2);
    GameObject* arbe = CreateTree(2, 2);
    lvl1->AddGameObject(caillou, { 8,2 });
    lvl1->AddGameObject(caillou2, { 9,2 });
    lvl1->AddGameObject(arbe, { 2,2 });
    createfloor(0, 0, 15, 100, sf::degrees(0), lvl1);
    lvl1->SetPlayer(player);
    lvl1->SetLvLData(lvlObject);
    return lvl1;
}
