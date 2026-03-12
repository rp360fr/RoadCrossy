#include "Extern.h"


sf::Vector2f calcMouvement(int x, int y)
{
    float screenX = (x - y) * 32;
    float screenY = (x + y) * 16;
    return sf::Vector2f(screenX, screenY);
}

sf::Vector2f scrolling(int x, int y)
{
    float screenX = (x - y) * 32;
    float screenY = (x + y) * 32;
    return sf::Vector2f(screenX, screenY);
}