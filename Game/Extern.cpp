#include "Extern.h"

std::vector <TileType> map = {};
sf::Vector2f* scrollOffset = nullptr;


void InitScrollOffset()
{
    if (!scrollOffset)
        scrollOffset = new sf::Vector2f({ 0, 0 });
}

sf::Vector2f scrolling(int x, int y)
{
    float screenX = (x - y) * 32;
    float screenY = (x + y) * 32;
    return sf::Vector2f(screenX, screenY);
}


int sens(TileType t)
{
    if (t == TileType::ROADL || t == TileType::WATERL || t == TileType::TRAINL)
        return 14;
    else if (t == TileType::ROADR || t == TileType::WATERR || t == TileType::TRAINR)
        return 0;
    else
        return 1234567890;
}

std::vector<TileType> CreateMapTab()
{
    return {
    TileType::GRASS,
    TileType::GRASS,
    TileType::GRASS,
    TileType::ROAD,
    TileType::ROAD,
    TileType::TRAIN,
    TileType::WATER,
    TileType::GRASS,
    TileType::ROAD,
    TileType::GRASS,
    TileType::GRASS,
    TileType::WATER,
    TileType::GRASS,
    TileType::ROAD,
    TileType::GRASS,
    TileType::GRASS,
    TileType::WATER,
    TileType::GRASS,
    TileType::ROAD,
    TileType::GRASS,
    TileType::GRASS,
    TileType::WATER,
    TileType::GRASS,
    TileType::ROAD,
    TileType::GRASS,
    TileType::TRAIN,
    TileType::WATER,
    TileType::GRASS,
    TileType::ROAD,
    TileType::GRASS,
    TileType::GRASS,
    TileType::WATER,
    TileType::GRASS,
    TileType::ROAD,
    TileType::GRASS,
    TileType::GRASS,
    TileType::WATER,
    TileType::GRASS,
    TileType::ROAD,
    TileType::TRAIN,
    TileType::GRASS,
    TileType::WATER,
    TileType::GRASS,
    TileType::ROAD,
    TileType::GRASS,
    TileType::GRASS,
    TileType::WATER,
    TileType::GRASS,
    TileType::ROAD,
    TileType::GRASS
    };
}
