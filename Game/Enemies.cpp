#include "Enemies.h"

GameObject* CreateTree(int x, int y) {
    GameObject* tree = new GameObject(x,y, scrollOffset);
    Collider* cl = new Collider(Red);
    SpriteRenderer* sr = new SpriteRenderer("Tree.png", { 64,64 }, { 1,1 });
    Variables* vr = new Variables();
    vr->addString("Type", "Block");
    tree->AddComponent(sr);
    tree->AddComponent(vr);
    tree->AddComponent(cl);
    return tree;
}



GameObject* CreateRock(int x,int y) {
    GameObject* rock = new GameObject(x,y, scrollOffset);
    SpriteRenderer* sr = new SpriteRenderer("Rock.png", { 64,64 }, { 1,1 });
    Variables* vr = new Variables();
    Collider* cl = new Collider(Red);
    vr->addString("Type","Block");
    rock->AddComponent(sr);
    rock->AddComponent(vr);
    rock->AddComponent(cl);
    return rock;
}


GameObject* CreateGrass(int x, int y) {
    GameObject* grass = new GameObject(x-1,y-1, scrollOffset);
    Collider* cl = new Collider(Blue);
    SpriteRenderer* sr = new SpriteRenderer("Grass.png", { 64,64 }, { 1,1 });
    Variables* vr = new Variables();
    vr->addString("Type", "Grass");
    grass->AddComponent(sr);
    grass->AddComponent(cl);
    grass->AddComponent(vr);
    return grass;
}

GameObject* CreateRoad(int x, int y) {
    GameObject* road = new GameObject(x-1, y - 1, scrollOffset);
    Collider* cl = new Collider(Blue);
    SpriteRenderer* sr = new SpriteRenderer("Road.png", { 64,64 }, { 1,1 });
    Variables* vr = new Variables();
    vr->addString("Type", "Grass");
    road->AddComponent(sr);
    road->AddComponent(cl);
    road->AddComponent(vr);
    return road;
}

GameObject* CreateRails(int x, int y) {
    GameObject* road = new GameObject(x - 1, y - 1, scrollOffset);
    Collider* cl = new Collider(Blue);
    SpriteRenderer* sr = new SpriteRenderer("Rails.png", { 64,64 }, { 1,1 });
    Variables* vr = new Variables();
    vr->addString("Type", "Grass");
    road->AddComponent(sr);
    road->AddComponent(cl);
    road->AddComponent(vr);
    return road;
}


GameObject* CreateWater(int x, int y)
{
    GameObject* water = new GameObject(x-1, y - 1, scrollOffset);
    SpriteRenderer* sr = new SpriteRenderer("Water.png", { 64,64 }, { 1,1 });
    Variables* vr = new Variables();
    vr->addString("Type", "Water");
    water->AddComponent(sr);
    water->AddComponent(vr);
    return water;
}

GameObject* CreateWaterHitbox(int x, int y)
{
    GameObject* water = new GameObject(x, y, scrollOffset);
    Variables* vr = new Variables();
    Collider* cl = new Collider(Red);
    vr->addString("Type", "Water");
    water->AddComponent(vr);
    water->AddComponent(cl);
    return water;
}

GameObject* CreateCar(int y, std::string sens)
{
    GameObject* car;
    if(sens == "Left")
        car = new GameObject(0, y, scrollOffset);
    else
        car = new GameObject(14, y, scrollOffset);
    SpriteRenderer* sr = new SpriteRenderer("Car.png", { 64,64 }, { 1,1 });
    Movement* mv = new Movement(sens);
    Variables* vr = new Variables();
    Collider* cl = new Collider(Red);
    vr->addString("Type", "Car");
    car->AddComponent(sr);
    car->AddComponent(vr);
    car->AddComponent(mv);
    car->AddComponent(cl);
    return car;
}

GameObject* CreateTrain(int y, std::string sens)
{
    GameObject* Train;
    if (sens == "Left")
        Train = new GameObject(0, y, scrollOffset);
    else
        Train = new GameObject(14, y, scrollOffset);
    SpriteRenderer* sr = new SpriteRenderer("Train.png", { 64,64 }, { 1,1 });
    Movement* mv = new Movement(sens);
    Variables* vr = new Variables();
    Collider* cl = new Collider(Red);
    vr->addString("Type", "Train");
    Train->AddComponent(sr);
    Train->AddComponent(vr);
    Train->AddComponent(mv);
    Train->AddComponent(cl);
    return Train;
}

GameObject* CreateTrain(int y,TileType t)
{
    std::string sens;
    if (t == TileType::TRAINL)
        sens = "Left";
    else
		sens = "Right";

    GameObject* Train;
    if (sens == "Left")
        Train = new GameObject(0, y, scrollOffset);
    else
        Train = new GameObject(14, y, scrollOffset);
    SpriteRenderer* sr = new SpriteRenderer("Train.png", { 64,64 }, { 1,1 });
    Movement* mv = new Movement(sens);
    Variables* vr = new Variables();
    Collider* cl = new Collider(Red);
    vr->addString("Type", "Train");
    Train->AddComponent(sr);
    Train->AddComponent(vr);
    Train->AddComponent(mv);
    Train->AddComponent(cl);
    return Train;
}


GameObject* CreateBoat(int y, std::string sens)
{
    GameObject* boat;
    if (sens == "Left")
        boat = new GameObject(0, y,scrollOffset);
    else
        boat = new GameObject(14, y,scrollOffset);
    SpriteRenderer* sr = new SpriteRenderer("Boat.png", { 64,64 }, { 1,1 });
    Movement* mv = new Movement(sens);
    Variables* vr = new Variables();
    Collider* cl = new Collider(Red);
    vr->addString("Type", "Boat");
    boat->AddComponent(sr);
    boat->AddComponent(vr);
    boat->AddComponent(mv);
    boat->AddComponent(cl);
    return boat;
}






