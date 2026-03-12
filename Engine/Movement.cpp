#include "Component.h"



void Movement::Start() {

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
    int speed = 1000;
    if (!owner)
    {
        std::cout << "[ERROR] Movement::Update - owner est null!" << std::endl;
        return;
    }
    if (owner->GetComponent<Variables>()->getString("Type") == "Car")
    {
        speed = 500;
    }
    if (sens == "Right")
        owner->getTransform().pos += { calc(1, 0).x / speed, calc(1, 0).y / speed };
    else
        owner->getTransform().pos += { calc(-1, 0).x / speed, calc(-1, 0).y / speed };
}