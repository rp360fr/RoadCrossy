#include "Projectiles.h"

GameObject* CreateProjectile(GameObject* player)
{

	GameObject* projectile = new GameObject({ 0, 0 });
	SpriteRenderer* sr = new SpriteRenderer("Projectile.png", { 16,16 }, { 2,1 });
	Projectile* pr = new Projectile(0.08f, Direction::Up, player);
	sr->setAnimated(true);
	projectile->AddComponent(sr);
	projectile->AddComponent(pr);
	projectile->SetPosition({ player->getTransform().pos.x + 24,player->getTransform().pos.y});
	return projectile;
}

GameObject* CreateEProjectile(GameObject* ennemie,GameObject* Player)
{

	GameObject* projectile = new GameObject({ ennemie->getTransform().pos.x + 24,ennemie->getTransform().pos.y +34});
	SpriteRenderer* sr = new SpriteRenderer("ProjectileE.png", { 16,16 }, { 2,1 });
	Projectile* pr = new Projectile(Player->getTransform().pos,0.05f, { ennemie->getTransform().pos.x + 24,ennemie->getTransform().pos.y + 73 }, ennemie);
	sr->setAnimated(true);
	projectile->AddComponent(sr);
	projectile->AddComponent(pr);
	return projectile;
}


GameObject* BossPhase1(GameObject* ennemie, GameObject* Player)
{
	static int pos = 0;
	GameObject* projectile = new GameObject({ ennemie->getTransform().pos.x + 24,ennemie->getTransform().pos.y + 134 });
	SpriteRenderer* sr = new SpriteRenderer("ProjectileE.png", { 16,16 }, { 2,1 });
	Projectile* pr = new Projectile({(float)pos,600}, 0.05f, {ennemie->getTransform().pos.x + 24,ennemie->getTransform().pos.y + 73}, ennemie);
	pos = (pos + 40) % 800;
	sr->setAnimated(true);
	projectile->AddComponent(sr);
	projectile->AddComponent(pr);
	return projectile;
}