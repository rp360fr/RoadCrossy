#include "Component.h"

Collider::Collider() {
	hitbox.setSize({ 64,32 });
	hitbox.setRotation(sf::degrees(45));
	hitbox.setFillColor({ sf::Color::Red });
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
	
	

}
void Collider::Render(sf::RenderWindow& window) {
	/*window.draw(hitbox);*/
}
bool Collider::DoesHitboxCollide(GameObject* target) {
	sf::FloatRect objBounds = owner->GetComponent<Collider>()->GetBounds();
	sf::FloatRect targetBounds = target->GetComponent<Collider>()->GetBounds();
	if (objBounds.findIntersection(targetBounds))
		return true;
	else
		return false;
}