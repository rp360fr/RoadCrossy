#include "Component.h"

Collider::Collider(sf::Color color) : hitbox(sf::Vector2f(1, 1))
{
	this->color = color;
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
	float x, y;
	if (owner->getBato())
	{
		x = 23 - owner->getBato()->GetComponent<Collider>()->getHitbox().getPosition().x;
		y = -owner->getBato()->GetComponent<Collider>()->getHitbox().getPosition().y;
	}
	else
	{
		x = 23 - hitbox.getPosition().x;
		y = -hitbox.getPosition().y;
	}
	sf::ConvexShape showHitbox;
	
	float isoX = (x - y) * 32;
	float isoY = (x + y) * 16;
	if (color == sf::Color::Red)
		showHitbox.setOrigin({ 0, -32 });
	sf::Vector2f transform = { isoX,isoY };
	transform += *owner->getTransform().deltaScrolling;
	showHitbox.setPosition(transform);
	showHitbox.setPointCount(4);

	float w = 64;
	float h = 32;

	showHitbox.setPoint(0, sf::Vector2f(0, h / 2));
	showHitbox.setPoint(1, sf::Vector2f(w / 2, 0));
	showHitbox.setPoint(2, sf::Vector2f(w, h / 2));
	showHitbox.setPoint(3, sf::Vector2f(w / 2, h));
	showHitbox.setOutlineThickness(1);
	showHitbox.setOutlineColor(sf::Color::Black);

	if (debugF3 && color == sf::Color::Red)
	{
		showHitbox.setFillColor(sf::Color::Red);
		window.draw(showHitbox);
	}
		
	if (debugF4 && color == sf::Color::Blue)
	{
		showHitbox.setFillColor(sf::Color::Blue);
		window.draw(showHitbox);

	}
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
	{
		return true;
	}
	return false;
}

