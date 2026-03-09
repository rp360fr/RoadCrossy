#include "Fond.h"

GameObject* createFond(std::string s)
{
	GameObject* fond = new GameObject({ 0,0 });
	SpriteRenderer* sr = new SpriteRenderer(s, { 128,64 }, { 0,0 });
	sr->setAnimated(false);
	sr->setFond(true);
	fond->AddComponent(sr);
	return fond;
}