#include "Enemies.h"

GameObject* CreateTree(sf::Vector2f vector) {
    GameObject* tree = new GameObject({ vector });
    SpriteRenderer* sr = new SpriteRenderer("tree.png", { 64,64 }, { 1,1 });
    tree->AddComponent(sr);
    return tree;
}



GameObject* CreateRock(int x,int y) {
    GameObject* rock = new GameObject({isometri(x,y)});
    SpriteRenderer* sr = new SpriteRenderer("Blocks_63.png", { 64,64 }, { 1,1 });
    Collider* cl = new Collider();
    rock->AddComponent(sr);
    rock->AddComponent(cl);
   /* cl->Hitbox(64, 32, sf::degrees(45));*/
    
    
    return rock;
}


GameObject* CreateGrass(int x, int y) {
    GameObject* grass = new GameObject(isometri(x,y));
    SpriteRenderer* sr = new SpriteRenderer("blocks_1.png", { 64,64 }, { 1,1 });
    grass->AddComponent(sr);

    return grass;
}








sf::Vector2f isometri(int x, int y)
{
    float screenX = (x - y) * tile_width / 2;
    float screenY = (x + y) * tile_height / 4;
    return sf::Vector2f(screenX, screenY);
}
