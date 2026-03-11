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
                 /*   obj->getTransform().pos += isometri(0,1);*/
                }
            });
        // Gestion des collisions
        Event::CreateEvent(-2, []()
            {
                Scene* currentScene = engineRef->getSceneModule()->GetActiveScene();
                if (currentScene == nullptr || currentScene->getName() == "Pause" ||
                    currentScene->getName() == "Menu" || currentScene->getName() == "GameOver")
                    return;
                InputHandler::CollisionProjectiles();
                InputHandler::CollisionVaisseau(); 
                InputHandler::CollisionBonusMalus();
                InputHandler::TestDeath();
                
            });


        eventsCreated = true;
    }
}


void InputHandler::CollisionProjectiles()
{
    for (GameObject* obj : engineRef->getSceneModule()->GetActiveScene()->getLstObj())
    {
        if (obj->GetComponent<Collider>() != nullptr && obj->GetComponent<Collider>()->getCollide() == true)
        {
            for (GameObject* target : engineRef->getSceneModule()->GetActiveScene()->getLstObj())
            {
                if (target->GetComponent<Projectile>() != nullptr)
                {
                    if (obj->GetComponent<Collider>()->DoesCollide(target) && target->GetComponent<Projectile>()->getShooter() != obj)
                    {
                        obj->GetComponent<Variables>()->MinusInt("PV", 1);
                        if (obj == engineRef->getSceneModule()->GetActiveScene()->GetPlayer())
                            engineRef->getSceneModule()->GetActiveScene()->GetPlayer()->GetComponent<SpriteRenderer>(1)->UpFrame();
                        std::cout << "touche, Pv : " << obj->GetComponent<Variables>()->getInt("PV") << std::endl;
                        target->Destroy();
                    }
                }
            }
        }
    }
}

void InputHandler::TestDeath()
{
    for (GameObject* obj : engineRef->getSceneModule()->GetActiveScene()->getLstObj())
    {
        if (obj->GetComponent<Collider>() != nullptr)
        {
            if (obj->GetComponent<Variables>()->getInt("PV") == 0)
            {
                if (obj == engineRef->getSceneModule()->GetActiveScene()->GetPlayer())
                {
                    Scene* GameOver = InputHandler::getThisScene(scenesRef, "GameOver");
                    engineRef->getSceneModule()->GetActiveScene()->GetLvLData()->GetComponent<AudioManager>()->Pause();
                    if (engineRef != nullptr)
                    {
                        GameOver->getThisObjByText("Retry")->setClickable(true);
                        GameOver->getThisObjByText("Quit")->setClickable(true);
                        engineRef->getSceneModule()->SetActiveScene(GameOver);
                        GameOver->Start();
                        engineRef->setGameState(false);
                    }
                }
                else
                {
                    int Bonus = rand() % 10 + 1;
                    if (Bonus >= 6)
                    {
                        GameObject* pUp = CreateHpUp(obj);
                        engineRef->getSceneModule()->GetActiveScene()->AddGameObject(pUp);
                        pUp->Start();
                    }
                    obj->GetComponent<Collider>()->setCollide(false);
                    std::cout << "mort" << std::endl;
                    obj->GetComponent<SpriteRenderer>()->setVisible(false);
                    obj->Destroy();
                } 
            }
        }
    }
}

void InputHandler::CollisionVaisseau()
{
    for (GameObject* obj : engineRef->getSceneModule()->GetActiveScene()->getLstObj())
    {
        if (obj->GetComponent<Collider>() != nullptr && obj->GetComponent<Collider>()->getCollide() == true && obj->GetComponent<Ennemie>() != nullptr)
        {
            for (GameObject* target : engineRef->getSceneModule()->GetActiveScene()->getLstObj())
            {
                if (target == engineRef->getSceneModule()->GetActiveScene()->GetPlayer())
                {
                    if (obj->GetComponent<Collider>()->DoesCollide(target))
                        target->GetComponent<Variables>()->addInt("PV", 0);
                        
                }
            }
        }
    }
}

void InputHandler::CollisionBonusMalus()
{
    for (GameObject* obj : engineRef->getSceneModule()->GetActiveScene()->getLstObj())
    {
        if (obj->GetComponent<Collider>() != nullptr && obj->GetComponent<Collider>()->getCollide() == true && obj->GetComponent<Variables>() != nullptr && obj->GetComponent<Variables>()->getString("Up")== "+1HP")
        {
            for (GameObject* target : engineRef->getSceneModule()->GetActiveScene()->getLstObj())
            {
                if (target == engineRef->getSceneModule()->GetActiveScene()->GetPlayer())
                {
                    if (obj->GetComponent<Collider>()->DoesCollide(target) && target->GetComponent<Variables>()->getInt("PV") <= 4)
                    {
                        target->GetComponent<Variables>()->PlusInt("PV", 1);
                        target->GetComponent<SpriteRenderer>(1)->DownFrame();
                        obj->Destroy();
                    }
                        
                }
            }
        }
    }
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