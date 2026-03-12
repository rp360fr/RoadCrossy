#include "Player.h"


GameObject* createPlayer(int x, int y)
{
	GameObject* player = new GameObject(x,y);
	SpriteRenderer* sr = new SpriteRenderer("blocks_1.png", { 64,64 }, { 3,3 });
	Variables* vr = new Variables();
	Collider* cl = new Collider();
	player->AddComponent(sr);
	player->AddComponent(vr);
	player->AddComponent(cl);
	return player;
}


