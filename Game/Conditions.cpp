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
        return true;
    }
    else
    {
        return false;
    }

}



bool ChangeLayer(std::vector<GameObject*>& obj, GameObject* player, char mv)
{
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
            player->getTransform().pos += calcMouvement(0, -1);
            sprite->setDirection(Direction::Left);
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
            player->getTransform().pos += calcMouvement(0, 1);
            sprite->setDirection(Direction::Left);
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
            player->getTransform().pos += calcMouvement(-1, 0);
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
            player->getTransform().pos += calcMouvement(1, 0);
            sprite->setDirection(Direction::Left);
        }
    }
}

void Conditions::Scrolling(Scene* lvl)
{
    if (debugF1)
    {
        for (GameObject* obj : lvl->getGroundObj())
        {
            obj->getTransform().pos += { scrolling(0, 2).x / 500, scrolling(0, 1).y / 500 };
        }
        for (GameObject* obj : lvl->getObstaclesObj())
        {
            if (obj != nullptr)
                obj->getTransform().pos += { scrolling(0, 2).x / 500, scrolling(0, 1).y / 500 };
        }
        for (GameObject* obj : lvl->getMovingObstaclesObj())
        {
            if (obj != nullptr)
                obj->getTransform().pos += { scrolling(0, 2).x / 500, scrolling(0, 1).y / 500 };
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
    for (GameObject* obj : lvl->getObstaclesObj())
    {
        if (obj)
        {
            if (obj->GetComponent<Collider>() != nullptr && obj != lvl->GetPlayer())
            {
                if (obj->GetComponent<Collider>()->DoesCollide(lvl->GetPlayer()))
                    return true;
            }
        }
    }
    return false;
}