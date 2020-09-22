#include "Food.h"


Food::Food(bool pvp)
{
	srand(time(NULL));

	int x;
	if (pvp)
		x = ((rand() % 14 + 1) * 48) + 24 + 768;
	else
		x = ((rand() % 14 + 1) * 48) + 24;

	int y = ((rand() % 14 + 1) * 48) + 24;

	this->sprite.setPosition(x, y);
}

void Food::newPosition(bool pvp)
{
	srand(time(NULL));

	int x;
	if (pvp)
		x = ((rand() % 14 + 1) * 48) + 24 + 768;
	else
		x = ((rand() % 14 + 1) * 48) + 24;

	int y = ((rand() % 14 + 1) * 48) + 24;

	this->sprite.setPosition(x,y);
}

void Food::setTexture(std::string texture)
{
	this->sprite.setTexture(ResourceHolder::loadTexture(texture));
	this->sprite.setScale(0.75, 0.75);

	this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2.f, this->sprite.getLocalBounds().height / 2.f);
}

sf::Vector2f Food::getPosition()
{
	return this->sprite.getPosition();
}

sf::Sprite& Food::getSprite()
{
	return this->sprite;
}

void Food::draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}
