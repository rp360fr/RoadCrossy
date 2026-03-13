#include "Component.h"

Collider::Collider(sf::Color color) 
{

	hitbox.setPointCount(4);

	float w = 64;
	float h = 32;

	hitbox.setPoint(0, sf::Vector2f(0, h / 2));
	hitbox.setPoint(1, sf::Vector2f(w / 2, 0));
	hitbox.setPoint(2, sf::Vector2f(w, h / 2));
	hitbox.setPoint(3, sf::Vector2f(w / 2, h));
	hitbox.setOutlineThickness(1);
	hitbox.setOutlineColor(sf::Color::Black);
	hitbox.setFillColor(color);
}

void Collider::Start()
{
	if(owner->GetComponent<Variables>() != nullptr)
		hitbox.setOrigin({ 0, -32 });
	hitbox.setPosition(owner->getTransform().pos);
}

void Collider::Update()
{
	hitbox.setPosition(owner->getTransform().pos);
}


void Collider::Render(sf::RenderWindow& window)
{
	if(debugF3 && hitbox.getFillColor() == sf::Color::Red)
		window.draw(hitbox);
	if(debugF4 && hitbox.getFillColor() == sf::Color::Blue)
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

	if (objBounds.contains(targetBounds.position))
	{
		if (owner->GetComponent<Variables>()->getString("Type") == "Boat")
			return false;
		return true;
	}
	return false;
}

