#include "Player.h"


GameObject* createPlayer()
{
	GameObject* player = new GameObject({ 200, 200 });
	SpriteRenderer* sr = new SpriteRenderer("Spaceship-Sheet.png", { 64,64 }, { 3,3 });
	SpriteRenderer* HP = new SpriteRenderer("HP.png", { 32,32 }, { 5,1 },true,1);
	HP->setScale(4.5);
	AudioManager* ad = new AudioManager("Shoot.wav");
	Collider* cl = new Collider();
	Variables* stats = new Variables();
	stats->addInt("PV", 5);
	player->AddComponent(ad);
	player->AddComponent(cl);
	player->AddComponent(sr);
	player->AddComponent(HP);
	player->SetPosition({ 300,200 });
	player->AddComponent(stats);
	return player;
}


GameObject* createTest()
{
	std::cout << "create test" << std::endl;
	GameObject* test = new GameObject({ 200, 200 });
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