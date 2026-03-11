#include "Enemies.h"

GameObject* CreateTree(int x, int y) {
    GameObject* tree = new GameObject(x,y);
    SpriteRenderer* sr = new SpriteRenderer("tree.png", { 64,64 }, { 1,1 });
    tree->AddComponent(sr);
    return tree;
}



GameObject* CreateRock(int x,int y) {
    GameObject* rock = new GameObject(x,y);
    SpriteRenderer* sr = new SpriteRenderer("Blocks_63.png", { 64,64 }, { 1,1 });
    rock->AddComponent(sr);
    return rock;
}


GameObject* CreateGrass(int x, int y) {
    GameObject* grass = new GameObject(x,y);
    SpriteRenderer* sr = new SpriteRenderer("blocks_1.png", { 64,64 }, { 1,1 });
    grass->AddComponent(sr);

    return grass;
}







