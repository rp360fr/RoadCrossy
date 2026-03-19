#pragma once
#include "Engine.h"

enum class TileType
{
    GRASS,
    ROAD,
    ROADR,
    ROADL,
    WATER,
    WATERR,
    WATERL,
    TRAIN,
    TRAINR,
    TRAINL
};

sf::Vector2f scrolling(int x, int y);
int sens(TileType t);
std::vector<TileType> CreateMapTab();
void InitScrollOffset();
std::string TileTypeToString(TileType t);

extern sf::Clock Invincibility;
extern sf::Vector2f* scrollOffset;
extern std::vector<TileType> map;