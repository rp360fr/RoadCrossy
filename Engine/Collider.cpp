#include "Component.h"

Collider::Collider() 
{

	hitbox.setPointCount(4);

	float w = 64;
	float h = 32;

	hitbox.setPoint(0, sf::Vector2f(0, h / 2));
	hitbox.setPoint(1, sf::Vector2f(w / 2, 0));
	hitbox.setPoint(2, sf::Vector2f(w, h / 2));
	hitbox.setPoint(3, sf::Vector2f(w / 2, h));
	hitbox.setOrigin({ 0, -32 });
	hitbox.setFillColor(sf::Color::Green);
}

void Collider::Start()
{
	hitbox.setPosition(owner->getTransform().pos);
}

void Collider::Update()
{
	
	hitbox.setPosition(owner->getTransform().pos);
}


void Collider::Render(sf::RenderWindow& window)
{
	window.draw(hitbox);
}

bool Collider::DoesCollide(GameObject* target)
{
	if (!target)
		return false;

	Collider* col = target->GetComponent<Collider>();
	if (!col)
		return false;
	
	sf::FloatRect objBounds = hitbox.getGlobalBounds();
	sf::FloatRect targetBounds = col->hitbox.getGlobalBounds();

	if (objBounds.findIntersection(targetBounds))
		return true;
	return false;
}