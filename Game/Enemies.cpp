#include "Enemies.h"

GameObject* CreateTree(int x, int y) {
    GameObject* tree = new GameObject(x,y);
    Collider* cl = new Collider(sf::Color::Red);
    SpriteRenderer* sr = new SpriteRenderer("blocks_3.png", { 64,64 }, { 1,1 });
    Variables* vr = new Variables();
    vr->addString("Type", "Block");
    tree->AddComponent(sr);
    tree->AddComponent(vr);
    tree->AddComponent(cl);
    return tree;
}



GameObject* CreateRock(int x,int y) {
    GameObject* rock = new GameObject(x,y);
    SpriteRenderer* sr = new SpriteRenderer("Blocks_63.png", { 64,64 }, { 1,1 });
    Variables* vr = new Variables();
    Collider* cl = new Collider(sf::Color::Red);
    vr->addString("Type","Block");
    rock->AddComponent(sr);
    rock->AddComponent(vr);
    rock->AddComponent(cl);
    return rock;
}


GameObject* CreateGrass(int x, int y) {
    GameObject* grass = new GameObject(x-2,y-2);
    Collider* cl = new Collider(sf::Color::Blue);
    SpriteRenderer* sr = new SpriteRenderer("blocks_1.png", { 64,64 }, { 1,1 });
    Variables* vr = new Variables();
    vr->addString("Type", "Grass");
    grass->AddComponent(sr);
    grass->AddComponent(cl);
    grass->AddComponent(vr);
    return grass;
}

GameObject* CreateWater(int x, int y)
{
    GameObject* water = new GameObject(x - 2, y - 2);
    SpriteRenderer* sr = new SpriteRenderer("blocks_69.png", { 64,64 }, { 1,1 });
    Variables* vr = new Variables();
    vr->addString("Type", "Water");
    water->AddComponent(sr);
    water->AddComponent(vr);
    return water;
}

GameObject* CreateWaterHitbox(int x, int y)
{
    GameObject* water = new GameObject(x, y);
    Variables* vr = new Variables();
    Collider* cl = new Collider(sf::Color::Red);
    vr->addString("Type", "Water");
    water->AddComponent(vr);
    water->AddComponent(cl);
    return water;
}

GameObject* CreateCar(int y, std::string sens)
{
    GameObject* car;
    if(sens == "Left")
        car = new GameObject(0, y);
    else
        car = new GameObject(14, y);
    SpriteRenderer* sr = new SpriteRenderer("blocks_28.png", { 64,64 }, { 1,1 });
    Movement* mv = new Movement(sens);
    Variables* vr = new Variables();
    Collider* cl = new Collider(sf::Color::Red);
    vr->addString("Type", "Car");
    car->AddComponent(sr);
    car->AddComponent(vr);
    car->AddComponent(mv);
    car->AddComponent(cl);
    return car;
}

GameObject* CreateBoat(int y, std::string sens)
{
    GameObject* boat;
    if (sens == "Left")
        boat = new GameObject(0, y);
    else
        boat = new GameObject(14, y);
    SpriteRenderer* sr = new SpriteRenderer("cercueil2.png", { 64,64 }, { 1,1 });
    Movement* mv = new Movement(sens);
    Variables* vr = new Variables();
    Collider* cl = new Collider(sf::Color::Red);
    vr->addString("Type", "Boat");
    boat->AddComponent(sr);
    boat->AddComponent(vr);
    boat->AddComponent(mv);
    boat->AddComponent(cl);
    return boat;
}






