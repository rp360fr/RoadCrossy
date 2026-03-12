#include "Component.h"

Collider::Collider() {
	
}

void Collider::Start()
{
	
}

void Collider::Update()
{
	
}




bool Collider::DoesCollide(GameObject* target)
{
	sf::FloatRect objBounds = owner->GetComponent<SpriteRenderer>()->getBounds();
	sf::FloatRect targetBounds = target->GetComponent<SpriteRenderer>()->getBounds();
	if (objBounds.findIntersection(targetBounds))
		return true;
	else
		return false;
}


void Collider::Hitbox(float x, float y,sf::Angle angle) {
	if (owner->GetComponent<Transform>() != nullptr && owner != nullptr); {
		hitbox.setPosition(owner->GetComponent<Transform>()->pos);
	}
	hitbox.setSize({ x,y });
	hitbox.setRotation(angle);
	hitbox.setFillColor({ sf::Color::Red });
	

}
void Collider::Render(sf::RenderWindow& window) {
	window.draw(hitbox);
}
bool Collider::DoesHitboxCollide(GameObject* target) {
	sf::FloatRect objBounds = owner->GetComponent<Collider>()->GetBounds();
	sf::FloatRect targetBounds = target->GetComponent<Collider>()->GetBounds();
	if (objBounds.findIntersection(targetBounds))
		return true;
	else
		return false;
}