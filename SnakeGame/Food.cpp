#include "Food.h"


Food::Food(bool pvp)
{
	newPosition(pvp);
}

void Food::newPosition(bool pvp)
{

	int x;
	if (pvp)
		x = ((rand() % 14 + 1) * 48) + 24 + 768;
	else
		x = ((rand() % 14 + 1) * 48) + 24;

	int y = ((rand() % 14 + 1) * 48) + 24;

	this->sprite.setPosition(x, y);
	this->position = sf::Vector2f(x, y);
}

void Food::setPosition(sf::Vector2f newPos)
{
	this->position = newPos;
}

void Food::setTexture(std::string texture)
{
	this->sprite.setTexture(ResourceHolder::loadTexture(texture));
	this->sprite.setScale(0.75, 0.75);

	this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2.f, this->sprite.getLocalBounds().height / 2.f);
}

sf::Vector2f Food::getPosition()
{
	return this->position;
}

sf::Sprite& Food::getSprite()
{
	return this->sprite;
}

void Food::draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}

void Food::animate()
{
	currentOffsetIndex++;
	if (currentOffsetIndex > 19)
	{
		currentOffsetIndex = 0;
	}

	this->sprite.setPosition(position.x, position.y + animationOffsets[currentOffsetIndex]);
}
