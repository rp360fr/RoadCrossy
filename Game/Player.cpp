#include "Player.h"


GameObject* createPlayer(int x, int y)
{
	GameObject* player = new GameObject(x,y);
	SpriteRenderer* sr = new SpriteRenderer("spritesheet.png", { 64,64 }, { 9,3 });
	sr->setAnimated(true);
	Variables* vr = new Variables();
	Collider* cl = new Collider();
	player->AddComponent(sr);
	player->AddComponent(vr);
	player->AddComponent(cl);
	return player;
}


