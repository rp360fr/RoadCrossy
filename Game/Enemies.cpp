#include "Enemies.h"




GameObject* CreateEnemiesType1()
{
    GameObject* enemies = new GameObject({ 200.0f, 200.0f });
    Variables* variable = new Variables();
    SpriteRenderer* sr = new SpriteRenderer("Mechant1.png", { 64,64 }, { 1,1 });
    Ennemie* en = new Ennemie();
    Collider* cl = new Collider();
    variable->addInt("Type", 1); 
    variable->addInt("PV", 5);
    enemies->AddComponent(en);
    enemies->AddComponent(sr); 
    enemies->AddComponent(variable); 

    return enemies;
}

GameObject* CreateEnemiesType2()
{
    GameObject* enemies = new GameObject({ 200.0f, 200.0f });
    Variables* variable = new Variables();
    SpriteRenderer* sr = new SpriteRenderer("Mechant2.png", { 64,64 }, { 1,1 });
    Movement* mv = new Movement(0.01f);
    Ennemie* en = new Ennemie();
    Collider* cl = new Collider();
    variable->addInt("Type", 2);
    variable->addInt("PV", 10);
    enemies->AddComponent(mv);
    enemies->AddComponent(en);
    enemies->AddComponent(sr);
    enemies->AddComponent(cl);
    enemies->AddComponent(variable);

    return enemies;
}

GameObject* CreateEnemiesMine()
{
    GameObject* enemies = new GameObject({ 200, 30 });
    Variables* variable = new Variables();
    Collider* cl = new Collider();
    Ennemie* en = new Ennemie();
    Movement* mv = new Movement(0.005f);
    SpriteRenderer* sr = new SpriteRenderer("mine.png", { 64,64 }, { 1,1 });
    variable->addInt("Type", 3);
    variable->addInt("PV", 40);
    enemies->AddComponent(mv);
    enemies->AddComponent(variable);
    enemies->AddComponent(en);
    enemies->AddComponent(sr);
    enemies->AddComponent(cl);
    enemies->AddComponent(variable);

    return enemies;
}

GameObject* CreateEnemiesBoss()
{
    GameObject* enemies = new GameObject({ 200, 30 });
    Variables* variable = new Variables();
    Collider* cl = new Collider();
    Ennemie* en = new Ennemie();
    Movement* mv = new Movement(0.005f);
    SpriteRenderer* sr = new SpriteRenderer("Boss.png", { 128,128 }, { 1,1 });
    variable->addInt("Type", 4);
    variable->addInt("PV", 50);
    enemies->AddComponent(mv);
    enemies->AddComponent(variable);
    enemies->AddComponent(en);
    enemies->AddComponent(sr);
    enemies->AddComponent(cl);
    enemies->AddComponent(variable);

    return enemies;
}


void SpawnEnemies(int type, float spawnx, Scene* scene)
{
    if (type == 1) {
        std::cout << "Enemy type1 a spawn";
        GameObject* mechant1 = CreateEnemiesType1();
        mechant1->SetPosition({ spawnx, -70 });
        scene->AddGameObject(mechant1);

        mechant1->Start();
    }
    if (type == 2) {
        std::cout << "Enemy type2 a spawn";
        GameObject* mechant2 = CreateEnemiesType2();
        mechant2->SetPosition({ spawnx, -70 });
        scene->AddGameObject(mechant2);

        mechant2->Start();
    }
    if (type == 3) {
        std::cout << "Enemy mine a spawn";
        GameObject* mine = CreateEnemiesMine();
        mine->SetPosition({ spawnx, -70 });
        scene->AddGameObject(mine);

        mine->Start();
    }
    if (type == 4) {
        std::cout << "Enemy mine a spawn";
        GameObject* Boss = CreateEnemiesBoss();
        Boss->SetPosition({ spawnx, -70 });
        scene->AddGameObject(Boss);

        Boss->Start();
    }
}



void BotAi(GameObject* Bot,Scene* LvL)
{
    int type;
    if (Bot != nullptr)
    {
        if (Bot->GetComponent<Variables>() != nullptr)
        {
            type = Bot->GetComponent<Variables>()->getInt("Type");
            switch (type)
            {
            case 1:
                if (rand() % 10 + 1 > 6)
                {
                    if (rand() % 10 + 1 > 7)
                    {
                        std::cout << "shoot ennemie type 1 focus " << std::endl;
                        GameObject* projectile = CreateEProjectile(Bot, LvL->GetPlayer());
                        projectile->GetComponent<Projectile>()->setDirection(Direction::Focus);
                        projectile->Start();
                        LvL->AddGameObject(projectile);
                    }
                    else
                    {
                        std::cout << "shoot ennemie type 1 normal" << std::endl;
                        GameObject* projectile = CreateEProjectile(Bot, LvL->GetPlayer());
                        projectile->GetComponent<Projectile>()->setDirection(Direction::Down);
                        projectile->Start();
                        LvL->AddGameObject(projectile);
                    }
                }
                break;
            case 2:
                if (rand() % 10 + 1 > 8)
                {
                    std::cout << "shoot ennemie type 2" << std::endl;
                    if (rand() % 10 + 1 > 5)
                    {
                        GameObject* projectile = CreateEProjectile(Bot, LvL->GetPlayer());
                        projectile->GetComponent<Projectile>()->setDirection(Direction::Focus);
                        projectile->Start();
                        LvL->AddGameObject(projectile);
                    }
                    else
                    {
                        GameObject* projectile = CreateEProjectile(Bot, LvL->GetPlayer());
                        projectile->GetComponent<Projectile>()->setDirection(Direction::Down);
                        projectile->Start();
                        LvL->AddGameObject(projectile);
                    }
                }
                break;
            case 4:
                if (Bot->GetComponent<Variables>()->getInt("PV") > 25)
                {
                    GameObject* projectile = BossPhase1(Bot, LvL->GetPlayer());
                    projectile->GetComponent<Projectile>()->setDirection(Direction::Focus);
                    projectile->Start();
                    LvL->AddGameObject(projectile);
                }
                else
                {
                    GameObject* projectile = CreateEProjectile(Bot, LvL->GetPlayer());
                    projectile->GetComponent<Projectile>()->setDirection(Direction::Focus);
                    projectile->Start();
                    LvL->AddGameObject(projectile);
                }
            }

        }

    }
}