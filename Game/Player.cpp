#include "Player.h"


GameObject* createPlayer(int x, int y)
{
	GameObject* player = new GameObject(x,y);
	SpriteRenderer* sr = new SpriteRenderer("blocks_1.png", { 64,64 }, { 3,3 });
	Variables* vr = new Variables();
	Collider* cl = new Collider();
	player->AddComponent(cl);
	player->AddComponent(sr);
	player->AddComponent(vr);
	return player;
}


GameObject* createTest()
{
	std::cout << "create test" << std::endl;
	GameObject* test = new GameObject(sf::Vector2f(200, 200));
	SpriteRenderer* sr = new SpriteRenderer("mechant1.png", { 64,64 }, { 3,3 });
	Collider* cl = new Collider();
	Variables* stats = new Variables();
	stats->addInt("PV", 10);
	stats->addString("Nom", "Roger");
	sr->setAnimated(true);
	test->AddComponent(sr);
	test->SetPosition({ 200,200 });
	test->AddComponent(stats);
	return test;
}