#include "PowerUp.h"


GameObject* CreateHpUp(GameObject* Ennemie)
{
	std::cout << "create Bonus" << std::endl;
	GameObject* Up = new GameObject(Ennemie->getTransform().pos);
	SpriteRenderer* sr = new SpriteRenderer("BonusPv.png", { 64,87 }, { 1,1 });
	Collider* cl = new Collider();
	Movement* mv = new Movement(0.01f);
	Variables* stats = new Variables();
	stats->addString("Up", "+1HP");
	stats->addInt("PV", 5);
	sr->setAnimated(false);
	Up->AddComponent(stats);
	Up->AddComponent(sr);
	Up->AddComponent(mv);
	Up->AddComponent(cl);
	return Up;
}