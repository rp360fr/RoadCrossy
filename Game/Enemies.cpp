#include "Enemies.h"

GameObject* CreateTree(int x, int y) {
    GameObject* tree = new GameObject(x,y);
    SpriteRenderer* sr = new SpriteRenderer("blocks_3.png", { 64,64 }, { 1,1 });
    Variables* vr = new Variables();
    tree->AddComponent(sr);
    tree->AddComponent(vr);
    return tree;
}



GameObject* CreateRock(int x,int y) {
    GameObject* rock = new GameObject(x,y);
    SpriteRenderer* sr = new SpriteRenderer("Blocks_63.png", { 64,64 }, { 1,1 });
    Variables* vr = new Variables();
    vr->addString("Type","Rock");
    rock->AddComponent(sr);
    rock->AddComponent(vr);
    return rock;
}


GameObject* CreateGrass(int x, int y) {
    GameObject* grass = new GameObject(x-2,y-2);
    SpriteRenderer* sr = new SpriteRenderer("blocks_1.png", { 64,64 }, { 1,1 });
    grass->AddComponent(sr);

    return grass;
}







