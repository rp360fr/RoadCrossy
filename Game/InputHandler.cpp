// InputHandler.cpp
#include "InputHandler.h"
#include "QTE.h"

Engine* InputHandler::engineRef = nullptr;
std::vector<Scene*>* InputHandler::scenesRef = nullptr;
bool InputHandler::eventsCreated = false;
ArrowMiniGame* InputHandler::qteGame = nullptr;
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
    }else if (sceneName == "QTE")
    {
        SetupQTEInputs(scene);
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
                    Event::SetEventTrue(2);
                Conditions::Recalibrage(lvl);
                if (Conditions::testWin(lvl))
                    Event::SetEventTrue(1);
                
            });

        Event::CreateEvent(2, []()
            {
                Scene* qte = InputHandler::getThisScene(scenesRef, "Qte");
                if (qte != nullptr)
                {
                    engineRef->getSceneModule()->SetActiveScene(qte);
                    InputHandler::SetupSceneInputs(qte, "QTE");
                    qte->Start();
                   

                }
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
            if (engineRef->getSceneModule()->GetActiveScene() == lvl)
            Conditions::MoveUp(player,lvl);
        });
    InputManager::RegisterKeyPress("Up", [player, lvl]()
        {
            if (engineRef->getSceneModule()->GetActiveScene() == lvl)
            Conditions::MoveUp(player, lvl);
        });


    InputManager::RegisterKeyPress("S", [player, lvl]()
        {
            if (engineRef->getSceneModule()->GetActiveScene() == lvl)
            Conditions::MoveDown(player,lvl);
        });
    InputManager::RegisterKeyPress("Down", [player, lvl]()
        {
            if (engineRef->getSceneModule()->GetActiveScene() == lvl)
            Conditions::MoveDown(player, lvl);
        });


    InputManager::RegisterKeyPress("Q", [player, lvl]()
        {
            if (engineRef->getSceneModule()->GetActiveScene() == lvl)
            Conditions::MoveLeft(player, lvl);
        });
    InputManager::RegisterKeyPress("Left", [player, lvl]()
        {
            if (engineRef->getSceneModule()->GetActiveScene() == lvl)
            Conditions::MoveLeft(player, lvl);
        });


    InputManager::RegisterKeyPress("D", [player, lvl]()
        {
            if (engineRef->getSceneModule()->GetActiveScene() == lvl)
            Conditions::MoveRight(player, lvl);
        });
    InputManager::RegisterKeyPress("Right", [player, lvl]()
        {
            if (engineRef->getSceneModule()->GetActiveScene() == lvl)
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
    Scene* Qte = CreateQtelvl();
    Scene* GameOver = CreateGameOver();
    scenesRef->push_back(Menu);
    scenesRef->push_back(LvL);
    scenesRef->push_back(GameOver);
    scenesRef->push_back(Qte);
    Conditions::scrollOffset = { 0,0 };


    engineRef->getSceneModule()->SetActiveScene(Menu);
    InputHandler::SetupSceneInputs(Menu, "LaunchMenu");

    engineRef->setGameState(true);

    std::cout << "=== JEU REINITIALISE ===\n\n\n\n" << std::endl;
}

void InputHandler::SetupQTEInputs(Scene* qte)
{
    if (qteGame != nullptr)
    {
        delete qteGame;
        qteGame = nullptr;
    }
    qteGame = new ArrowMiniGame();

     // ← récupérer lvl

    Event::CreateEvent(-1, [qte]() // ← capturer lvl
        {
            Scene* lvl = InputHandler::getThisScene(scenesRef, "LvL");
            if (qteGame == nullptr) return;

            qteGame->update(qte);

            if (qteGame->isFinished())
            {
				qteGame->hide(qte);

                bool won = qteGame->playerWon();
                delete qteGame;
                qteGame = nullptr;

                // ← réarmer la mort pour la prochaine fois
               
                if (won)
                {
                    eventsCreated = false;
                    engineRef->getSceneModule()->SetActiveScene(lvl);
                    InputHandler::SetupSceneInputs(lvl, "LvL");
					Event::ResetEvent(2); 
                }
                else
                {
                    Scene* GameOver = InputHandler::getThisScene(scenesRef, "GameOver");
                    GameOver->getThisObjByText("Retry")->setClickable(true);
                    GameOver->getThisObjByText("Quit")->setClickable(true);
                    engineRef->getSceneModule()->SetActiveScene(GameOver);
                    GameOver->Start();
                    engineRef->setGameState(false);
                }
            }
        });
}
