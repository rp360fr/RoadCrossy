#include "Conditions.h"


bool moveElement(Scene* lvl, int posStart,char D)
{
    GameObject* player = lvl->GetPlayer();
    switch (D)
    {
    case 'U':
        player->getTransform().placement = posStart + 15;
        break;
    case 'D':
        player->getTransform().placement = posStart - 15;
        break;
    case 'L':
        player->getTransform().placement = posStart + 1;
        break;
    case 'R':
        player->getTransform().placement = posStart - 1;
        break;
    }
    player->getTransform().pos = { (float)(player->getTransform().placement % 15),(float)(player->getTransform().placement / 15) };
    player->GetComponent<Collider>()->Update();
    GameObject* collide = Conditions::Collision(lvl, D);
    if(collide)
    {
        if (collide->GetComponent<Variables>()->getString("Type") == "Boat")
        {
            Debug::DebugCout("Bato", 3);
            player->setBato(collide);
            player->getTransform().placement = collide->getTransform().placement;
            player->AddComponent(new Movement(collide->GetComponent<Movement>()->getSens(),collide->GetComponent<Movement>()->speed));
        }
        else if (collide->GetComponent<Variables>()->getString("Type") == "Block")
        {
            Debug::DebugCout("Block", 3);
            if(player->getBato() == nullptr)
                player->getTransform().placement = posStart;
        }
        
    }
    else
    {
        Debug::DebugCout("Rien", 3);
        Conditions::DelPlayer(lvl);
        lvl->getObstaclesObj()[player->getTransform().placement] = player;
        if (player->getBato())
            player->setBato(nullptr);
        else
            lvl->getObstaclesObj()[posStart] = nullptr;
    }
    Debug::DebugCout("pos player " + std::to_string(player->getTransform().placement), 2);
    return true;
}

void Conditions::DelPlayer(Scene* lvl)
{
    for (int i = 0; i<lvl->getObstaclesObj().size();i++)
    {
        if (lvl->getObstaclesObj()[i] == lvl->GetPlayer())
        {
            lvl->getObstaclesObj()[i] = nullptr;
            break;
        }
    }
}


bool ChangeLayer(Scene* lvl, GameObject* player, char mv)
{
    if (!debugF1)
        Debug::ChangeDebug(1);
    player->RemoveComponent<Movement>();
    bool test = false;
    int id = player->getTransform().placement;



    switch (mv)
    {
    case 'U': if (id + 15 < 1500) test = moveElement(lvl, id,'U'); break;
    case 'D': if (id - 15 >= 0) test = moveElement(lvl, id,'D'); break;
    case 'R': if (id - 1 >= 0) test = moveElement(lvl, id,'R'); break;
    case 'L': if (id + 1 < 1500) test = moveElement(lvl, id,'L'); break;
    }
    
    return test;
}

void Conditions::MoveUp(GameObject* player,Scene* lvl)
{
    if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
    {
        if (ChangeLayer(lvl, player, 'U'))
        {
            SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
            player->getTransform().pos = { (float)(player->getTransform().placement % 15),(float)(player->getTransform().placement / 15) };
            sprite->setDirection(Direction::Up);
        }

    }
}

void Conditions::MoveDown(GameObject* player, Scene* lvl)
{
    if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
    {
        if (ChangeLayer(lvl, player, 'D'))
        {
            SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
            player->getTransform().pos = { (float)(player->getTransform().placement % 15),(float)(player->getTransform().placement / 15) };
            sprite->setDirection(Direction::Down);
        }

    }
}

void Conditions::MoveLeft(GameObject* player,Scene* lvl)
{
    if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
    {
        if (ChangeLayer(lvl, player, 'L'))
        {
            SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
            player->getTransform().pos = { (float)(player->getTransform().placement % 15),(float)(player->getTransform().placement / 15) };
            sprite->setDirection(Direction::Left);
        }
    }
}


void Conditions::MoveRight(GameObject* player,Scene* lvl)
{
    if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
    {
        if (ChangeLayer(lvl, player, 'R'))
        {
            SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
            player->getTransform().pos = { (float)(player->getTransform().placement % 15),(float)(player->getTransform().placement / 15) };
            sprite->setDirection(Direction::Right);
        }
    }
}



void Conditions::Scrolling(Scene* lvl)
{
    if (debugF1)
    {
        sf::Vector2f delta = { scrolling(0, 2).x / 1200, scrolling(0, 1).y / 1200 };
        *scrollOffset += delta;         
    }
}

bool Conditions::testWin(Scene* lvl)
{
    if (lvl->GetPlayer()->getTransform().placement >= 735)
        return true;
    return false;
}

CollideType Conditions::Collision(Scene* lvl)
{
    GameObject* player = lvl->GetPlayer();
    int placement = player->getTransform().placement;
    sf::Vector2f posPlayer = player->GetComponent<SpriteRenderer>()->getSprite().getPosition();
    std::vector<GameObject*>& list = lvl->getObstaclesObj();
    std::vector<GameObject*>& listGround = lvl->getGroundObj();
    if (placement % 15 == 0 || placement % 15 == 15 && player->getBato())
        return CollideType::Dead;
    if (posPlayer.x < -64 || posPlayer.y > 864)
        return CollideType::Dead;
    for (GameObject* obj : list)
    {
        if (obj && obj != player)
        {
			const std::string& type = obj->GetComponent<Variables>()->getString("Type");
            if (obj->GetComponent<Collider>()->DoesCollide(player)) 
            {
                if (type == "Car" || type == "Train")
                    return CollideType::Dead;
            }
        }
    }
    for (GameObject* obj : listGround)
    {
        if (obj && obj != player)
        {
            if(obj->GetComponent<Collider>())
            if (obj->GetComponent<Collider>()->DoesCollide(player))
            {
                if (obj->GetComponent<Variables>()->getString("Type") == "Water" && player->getBato()==nullptr)
                    return CollideType::Dead;
            }
        }
    }
    return CollideType::Null;
}

GameObject* Conditions::Collision(Scene* lvl,char D)
{
    GameObject* player = lvl->GetPlayer();
    std::vector<GameObject*>& list = lvl->getObstaclesObj();

    for (GameObject* obj : list)
    {
        if (obj && obj != player)
        {
            if (obj->GetComponent<Collider>()->DoesCollide(player))
            {
                return obj;
            }
        }
    }
    return nullptr;
}


void Conditions::Recalibrage(Scene* lvl)
{
    std::vector<GameObject*>& list = lvl->getObstaclesObj();
    GameObject* player = lvl->GetPlayer();
    for (GameObject* obj : list)
    {
        if (obj)
        {
            if (player->getBato() == obj)
            {
                player->getTransform().placement = obj->getTransform().placement;
            }
            if (obj->GetComponent<Movement>())
            {
                int pos = obj->getTransform().placement;
                int cpt = obj->GetComponent<Movement>()->cpt;
                int speed = obj->GetComponent<Movement>()->speed;
                std::string sens = obj->GetComponent<Movement>()->getSens();
                if (cpt >= speed && obj != player)
                {
                    if (sens == "Left")
                    {
                        if (obj->getTransform().placement == obj->getTransform().posBase + 14)
                        {
                            lvl->getObstaclesObj()[pos] = nullptr;
                            obj->Destroy();
                        }
                        else
                        {
                            lvl->getObstaclesObj()[pos + 1] = obj;
                            lvl->getObstaclesObj()[pos] = nullptr;
                            obj->getTransform().placement = pos + 1;
                        }
                    }
                    else if(sens == "Right")
                    {
                        if (obj->getTransform().placement == obj->getTransform().posBase - 14)
                        {
                            lvl->getObstaclesObj()[pos] = nullptr;
                            obj->Destroy();
                        }
                        else
                        {
                            lvl->getObstaclesObj()[pos - 1] = obj;
                            lvl->getObstaclesObj()[pos] = nullptr;
                            obj->getTransform().placement = pos - 1;
                        }
                    }
                    obj->GetComponent<Movement>()->cpt = 0;
                }
            }
        }
    }
}

void Conditions::Replace(GameObject* obj, std::string sens)
{
    if(sens == "Right")
        obj->getTransform().pos += { 15, 0 };
    else
    {
        obj->getTransform().pos -= { 15, 0 };
    }
}

