#include "Component.h"

SpriteRenderer::SpriteRenderer():
	sprite(texture)
{

}

SpriteRenderer::SpriteRenderer(std::string s,sf::Vector2i size, std::array<int, 2> tab, bool b, int id) :
	sprite(texture)
{
	texturePath = "./Assets/"+s;
	this->size = size;
	AnimationParam = tab;
	std::cout << "Loading texture: " << texturePath << std::endl;
	Special = b;
	setId(id);
}

void SpriteRenderer::Start()
{
	if (!texture.loadFromFile(texturePath)) {
		std::cout << "erreur avec le chargement de la texture " << texturePath;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect({ 0,0 }, size));
}

void SpriteRenderer::Update()
{
	
}


void SpriteRenderer::Render(sf::RenderWindow& window)
{
	float x;
	float y;
	if (owner->getBato())
	{
		x = 20 - owner->getBato()->getTransform().pos.x;
		y = -owner->getBato()->getTransform().pos.y;
	}
	else
	{
		x = 20 - owner->getTransform().pos.x;
		y = -owner->getTransform().pos.y;
	}
	
	float isoX = (x - y) * 32;
	float isoY = (x + y) * 16;
	
	sf::Vector2f transform = { isoX,isoY };
	transform += owner->getTransform().deltaScrolling;
	sprite.setPosition(transform);
	if (Special == false)
	{
		if (!texture.isRepeated())
		{
			if (animated == true)
			{
				if (getDirection() == Direction::Left)
				{
					if (animationClock.getElapsedTime().asMilliseconds() > 80)
					{
						currentFrame = (currentFrame + 1) % AnimationParam[0];
						sprite.setTextureRect(sf::IntRect({ currentFrame * size.x, 0 }, { size.x, size.x }));
						animationClock.restart();
					}
				}
				else if (getDirection() == Direction::Right)
				{
					if (animationClock.getElapsedTime().asMilliseconds() > 80)
					{
						currentFrame = (currentFrame + 1) % AnimationParam[0];
						sprite.setTextureRect(sf::IntRect({ currentFrame * size.x, size.x % (AnimationParam[1] * size.x) }, { size.x, size.x }));
						animationClock.restart();
					}
				}
				else if (getDirection() == Direction::Up)
				{
					if (animationClock.getElapsedTime().asMilliseconds() > 80)
					{
						currentFrame = (currentFrame + 1) % AnimationParam[0];
						sprite.setTextureRect(sf::IntRect({ currentFrame * size.x, size.x * 2 % (AnimationParam[1] * size.x) }, { size.x, size.x }));
						animationClock.restart();
					}
				}
				else if (getDirection() == Direction::Down)
				{
					if (animationClock.getElapsedTime().asMilliseconds() > 80)
					{
						if (AnimationParam[1] < 4)
						{
							currentFrame = (currentFrame + 1) % AnimationParam[0];
							sprite.setTextureRect(sf::IntRect({ currentFrame * size.x, size.x * 2 }, { size.x, size.x }));
							animationClock.restart();
						}
						else
						{
							currentFrame = (currentFrame + 1) % AnimationParam[0];
							sprite.setTextureRect(sf::IntRect({ currentFrame * size.x, size.x * 3 }, { size.x, size.x }));
							animationClock.restart();
						}
					}
				}
			}
			else
			{
				sprite.setTextureRect(sf::IntRect({ 0 * size.x, 0 }, { size.x, size.x }));
			}
		}
	}
	else
	{
		sprite.setTextureRect(sf::IntRect({ currentFrame * size.x, 0 }, { size.x, size.x }));
		sprite.setPosition({ 650,500 });
	}
	if(visible == true)
		window.draw(sprite);
}


void SpriteRenderer::setFond(bool B)
{
	 texture.setRepeated(B); 
	 sprite.setTexture(texture);
	 sprite.setTextureRect(sf::IntRect({ 0,0 }, { 800,-5000 }));

}