#include "Conditions.h"


bool moveElement(std::vector<GameObject*>& list, int posStart, int posFin)
{
    GameObject* elem = list[posStart];
    if (list[posFin] == nullptr)
    {
        elem->getTransform().placement = posFin;
        list[posFin] = elem;
        list[posStart] = nullptr;
        Debug::DebugCout("pos joueur tab " + std::to_string(posFin), 2);
        if (elem->getBato() != nullptr)
        {
            list[elem->getBato()->getTransform().placement] = elem->getBato();
            elem->setBato(nullptr);
        }
        return true;
    }
    else if (list[posFin]->GetComponent<Collider>())
    {
        return true;
    }
    else
    {
        return false;
    }

}



bool ChangeLayer(std::vector<GameObject*>& obj, GameObject* player, char mv)
{
    if (player->getBato() != nullptr)
    {
        player->getBato()->getTransform().placement = player->getTransform().placement;
    }
        
    player->RemoveComponent<Movement>();
    int id = -1;
    bool test = false;
    for (int i = 0; i < obj.size(); i++)
    {
        if (obj[i] == player)
        {
            id = i;
            break;
        }
    }

    if (id == -1) return false;



    switch (mv)
    {
    case 'U': if (id + 15 < 1500) test = moveElement(obj, id, id + 15); break;
    case 'D': if (id - 15 >= 0) test = moveElement(obj, id, id - 15); break;
    case 'R': if (id - 1 >= 0) test = moveElement(obj, id, id - 1); break;
    case 'L': if (id + 1 < 1500) test = moveElement(obj, id, id + 1); break;
    }
    
    return test;
}

void Conditions::MoveUp(GameObject* player, std::vector<GameObject*>& lstObj)
{
    if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
    {
        if (ChangeLayer(lstObj, player, 'U'))
        {
            SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
            player->getTransform().pos = { player->getTransform().pos.x,player->getTransform().pos.y + 1 };
            sprite->setDirection(Direction::Up);
        }

    }
}

void Conditions::MoveDown(GameObject* player, std::vector<GameObject*>& lstObj)
{
    if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
    {
        if (ChangeLayer(lstObj, player, 'D'))
        {
            SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
            player->getTransform().pos = { player->getTransform().pos.x,player->getTransform().pos.y - 1 };
            sprite->setDirection(Direction::Down);
        }

    }
}

void Conditions::MoveLeft(GameObject* player, std::vector<GameObject*>& lstObj)
{
    if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
    {
        if (ChangeLayer(lstObj, player, 'L'))
        {
            SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
            player->getTransform().pos = { player->getTransform().pos.x + 1,player->getTransform().pos.y };
            sprite->setDirection(Direction::Left);
        }
    }
}


void Conditions::MoveRight(GameObject* player, std::vector<GameObject*>& lstObj)
{
    if (player != nullptr && player->GetComponent<SpriteRenderer>() != nullptr)
    {
        if (ChangeLayer(lstObj, player, 'R'))
        {
            SpriteRenderer* sprite = player->GetComponent<SpriteRenderer>();
            player->getTransform().pos = { player->getTransform().pos.x - 1, player->getTransform().pos.y };
            sprite->setDirection(Direction::Right);
        }
    }
}

sf::Vector2f Conditions::scrollOffset = { 0, 0 };

void Conditions::Scrolling(Scene* lvl)
{
    if (debugF1)
    {
        sf::Vector2f delta = { scrolling(0, 2).x / 500, scrolling(0, 1).y / 500 };
        scrollOffset += delta; // ? on accumule l'offset total

        for (GameObject* obj : lvl->getGroundObj())
            obj->getTransform().deltaScrolling = scrollOffset;
        for (GameObject* obj : lvl->getObstaclesObj())
            if (obj != nullptr)
            {
                if (obj->getBato() != nullptr)
                    obj->getBato()->getTransform().deltaScrolling = scrollOffset;
                obj->getTransform().deltaScrolling = scrollOffset;
            }
                
    }
}

bool Conditions::testWin(Scene* lvl)
{
    if (lvl->GetPlayer()->getTransform().placement >= 1485)
        return true;
    return false;
}

bool Conditions::Collision(Scene* lvl)
{
    GameObject* player = lvl->GetPlayer();
    std::vector<GameObject*>& list = lvl->getObstaclesObj();

    for (GameObject* obj : lvl->getObstaclesObj())
    {
        if (obj)
        {
            if (obj->GetComponent<Collider>() != nullptr && obj != lvl->GetPlayer() && obj->GetComponent<Variables>()->getString("Type") == "Boat" && player->getBato() == nullptr)
            {
                if (obj->GetComponent<Collider>()->DoesCollide(lvl->GetPlayer()))
                {
                    std::cout << "collision bato";
                    int posStart = player->getTransform().placement;
                    int posFin = obj->getTransform().placement;
                    player->getTransform().placement = posFin;
                    player->setBato(list[posFin]);
                    player->AddComponent(new Movement(list[posFin]->GetComponent<Movement>()->getSens()));
                    list[posFin] = player;
                    list[posStart] = nullptr;
                    Debug::DebugCout("pos joueur tab " + std::to_string(posFin), 2);
                    return false;
                }
            }
            else if (obj->GetComponent<Collider>() != nullptr && obj != lvl->GetPlayer() && obj->GetComponent<Variables>()->getString("Type") != "Boat")
            {
                if (obj->GetComponent<Collider>()->DoesCollide(lvl->GetPlayer()))
                    return true;
            }
        }
    }
    return false;
}

void Conditions::Recalibrage(Scene* lvl)
{
    int i = 0;
    for (GameObject* obj : lvl->getObstaclesObj())
    {
        if(obj)
            if (obj->GetComponent<Movement>())
            {
                i++;
                int pos = obj->getTransform().placement;
                int cpt = obj->GetComponent<Movement>()->cpt;
                int speed = obj->GetComponent<Movement>()->speed;
                std::string sens = obj->GetComponent<Movement>()->getSens();
                if (cpt >= speed)
                { 
                    if (sens == "Left")
                    {
                            if (obj->getTransform().placement == obj->getTransform().posBase + 14)
                            {
                                lvl->getObstaclesObj()[pos - 14] = obj;
                                lvl->getObstaclesObj()[pos] = nullptr;
                                obj->getTransform().placement = pos - 14;
                                Conditions::Replace(obj, "Left");
                                obj->GetComponent<Movement>()->speed = rand() % 250 + 100;
                            }
                            else
                            {
                                lvl->getObstaclesObj()[pos + 1] = obj;
                                lvl->getObstaclesObj()[pos] = nullptr;
                                obj->getTransform().placement = pos + 1;
                            }
                    }
                    else
                    {
                        if (obj->getTransform().placement == obj->getTransform().posBase - 14)
                        {
                            lvl->getObstaclesObj()[pos + 14] = obj;
                            lvl->getObstaclesObj()[pos] = nullptr;
                            obj->getTransform().placement = pos + 14;
                            Conditions::Replace(obj, "Left");
                            obj->GetComponent<Movement>()->speed = rand() % 250 + 100;
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

void Conditions::Replace(GameObject* obj, std::string sens)
{
    if(sens == "Right")
        obj->getTransform().pos += { 15,0};
    else
    {
        obj->getTransform().pos -= { 15,0 };
    }
}

void Conditions::Clean(std::vector<GameObject*>& tab, GameObject* obj, std::string sens)
{
    if (sens == "Left")
    {
        for (int i = 0; i < 14; i++)
        {
            tab[obj->getTransform().posBase + i] = nullptr;
        }
    }
    else
    {
        for (int i = 0; i < 14; i++)
        {
            tab[obj->getTransform().posBase - i] = nullptr;
        }
    }
}