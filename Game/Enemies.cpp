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
    Collider* cl = new Collider(sf::Color::Blue);
    SpriteRenderer* sr = new SpriteRenderer("blocks_1.png", { 64,64 }, { 1,1 });
    grass->AddComponent(sr);
    grass->AddComponent(cl);

    return grass;
}

GameObject* CreateWater(int x, int y)
{
    GameObject* water = new GameObject(x - 2, y - 2);
    SpriteRenderer* sr = new SpriteRenderer("blocks_69.png", { 64,64 }, { 1,1 });
    Collider* cl = new Collider(sf::Color::Blue);
    water->AddComponent(sr);
    water->AddComponent(cl);

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
        car = new GameObject(15, y);
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

GameObject* CreateBoat(int x, int y, std::string sens)
{
    GameObject* boat = new GameObject(x, y-1);
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






