#include "Component.h"



void Movement::Start() 
{
    if (owner->GetComponent<Variables>()->getString("Type") == "Car")
    {
        speed = rand() % 250 + 100;
    }
    else
    {
        speed = 500;
    }
}

void Movement::Render(sf::RenderWindow& window) {
    if (!owner) {
        std::cout << "[ERROR] Movement::Render - owner est null!" << std::endl;
        return;
    }

}

sf::Vector2f Movement::calc(int x, int y)
{

        float screenX = (x - y) * 32;
        float screenY = (x + y) * 16;
        return sf::Vector2f(screenX, screenY);
}

void Movement::Update() 
{
    if (!owner)
    {
        std::cout << "[ERROR] Movement::Update - owner est null!" << std::endl;
        return;
    }
    
    if (sens == "Right")
    {
        owner->getTransform().pos += { calc(1, 0).x / speed, calc(1, 0).y / speed };
        cpt++;
    }
    else
    {
        owner->getTransform().pos += { calc(-1, 0).x / speed, calc(-1, 0).y / speed };
        cpt++;
    }
        
}