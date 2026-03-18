#include "Player.h"


GameObject* createPlayer(int x, int y)
{
	GameObject* player = new GameObject(x,y, scrollOffset);
	SpriteRenderer* sr = new SpriteRenderer("Player.png", { 64,64 }, { 3,3 });
	Variables* vr = new Variables();
	Collider* cl = new Collider(sf::Color::Red);
	player->AddComponent(sr);
	player->AddComponent(vr);
	player->AddComponent(cl);
	return player;
}


