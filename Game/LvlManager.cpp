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
            Scene* lvl1 = InputHandler::getThisScene(lstScene, "LvL1");

            Engine* engine = InputHandler::GetEngine();
            if (engine != nullptr)
            {
                engine->getSceneModule()->SetActiveScene(lvl1);
                InputHandler::SetupSceneInputs(lvl1, "LvL1");
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




Scene* CreatePause()
{
    Scene* Pause = new Scene("Pause");
    GameObject* PauseObject = new GameObject({ 0,0 });
    AudioManager* ad = new AudioManager("PauseSound.mp3",0);
    AudioManager* ad2 = new AudioManager("ResumeSound.mp3",1);
    Variables* v = new Variables();
    GameObject* fond = createFond("SpaceBackGround.png");
    PauseObject->AddComponent(ad);
    PauseObject->AddComponent(ad2);
    Pause->SetLvLData(PauseObject);
    GameObject* Resume = createResume();
    GameObject* Quit = createQuit();
    Resume->setClickable(false);
    Quit->setClickable(false);
    Pause->AddGameObject(fond);
    Pause->AddGameObject(Resume);
    Pause->AddGameObject(Quit);
   
    InputManager::RegisterClickableObject(Resume, [Resume, Quit](GameObject* obj) 
        {
            std::cout << "Resume cliqué !" << std::endl;
            Scene* lvlactif = InputHandler::GetTempPauseScene();
            Engine* engine = InputHandler::GetEngine();
            if (engine != nullptr)
            {
                InputHandler::GetPauseScene()->getThisObjByText("Resume")->setClickable(false);
                InputHandler::GetPauseScene()->getThisObjByText("Quit")->setClickable(false);
                InputHandler::GetPauseScene()->GetLvLData()->GetComponent<AudioManager>(1)->Play();
                InputHandler::GetEngine()->getSceneModule()->SetActiveScene(InputHandler::GetTempPauseScene());
                InputHandler::GetTempPauseScene()->GetLvLData()->GetComponent<AudioManager>()->Play();

            }
        });

    InputManager::RegisterClickableObject(Quit, [](GameObject* obj) {
        std::cout << "Quit cliqué !" << std::endl;
        exit(0);
        });
    
    return Pause;
}

Scene* CreateGameOver()
{
    Scene* GameOver = new Scene("GameOver");
    GameObject* Retry = createRetry();
    GameObject* Quit = createQuit();
    GameObject* fond = createFond("SpaceBackGround.png");
    GameObject* GameOverObject = new GameObject({ 0,0 });
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



Scene* CreateLvL1()
{
    Scene* lvl1 = new Scene("LvL1");
    GameObject* lvlObject = new GameObject({0,0});
    AudioManager* ad = new AudioManager("SpaceMainTheme.mp3");
    ad->SetLoop(true);
    lvlObject->AddComponent(ad);
    GameObject* player = createPlayer();
    GameObject* fond = createFond();
    GameObject* Enemie = CreateEnemiesType1();
    lvl1->AddGameObject(Enemie);
    lvl1->AddGameObject(fond);
    lvl1->AddGameObject(player);
    lvl1->SetPlayer(player);
    lvl1->SetLvLData(lvlObject);
    return lvl1;
}


Scene* CreateLvL2()
{
    Scene* lvl2 = new Scene("LvL2");
    GameObject* lvlObject = new GameObject({ 0,0 });
    AudioManager* ad = new AudioManager("SpaceMainTheme.mp3");
    ad->SetLoop(true);
    lvlObject->AddComponent(ad);
    GameObject* player = createPlayer();
    GameObject* fond = createFond();

    lvl2->AddGameObject(fond);
    lvl2->AddGameObject(player);
    lvl2->SetPlayer(player);
    lvl2->SetLvLData(lvlObject);
    return lvl2;
}

Scene* CreateLvL3()
{
    Scene* lvl = new Scene("LvL3", { 800, 600 });

    GameObject* fond = createFond();
    GameObject* player = createPlayer();
    GameObject* LvLData = new GameObject({ 0, 0 });

    AudioManager* ambiance = new AudioManager("Ambiance.wav");
    AudioManager* pause = new AudioManager("MenuPause.wav", 1);
    ambiance->SetLoop(true);

    LvLData->AddComponent(ambiance);
    LvLData->AddComponent(pause);

    lvl->SetLvLData(LvLData);
    lvl->AddGameObject(fond);
    lvl->AddGameObject(player);
    lvl->AddGameObject(LvLData);
    lvl->SetPlayer(player);

    return lvl;
}