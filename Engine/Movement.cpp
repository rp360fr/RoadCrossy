#include "Component.h"



void Movement::Start() 
{
    const std::string& type = owner->GetComponent<Variables>()->getString("Type");
    if (type == "Car" || type == "Boat")
    {
        speed = rand() % 250 + 100;

    }
    else if (type == "Train")
    {
        speed = 50;
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
        
        owner->getTransform().pos -= { (float)1.0/speed, 0 };
        cpt++;
    }
    else
    {
        owner->getTransform().pos += { float(1.0)/speed, 0 };
        cpt++;
    }
}