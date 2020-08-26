#include "Segment.h"


Segment::Segment()
{
	this->dir = Direction::west;
}

void Segment::setPosition(int x, int y)
{
	this->sprite.setPosition(x, y);
}

void Segment::setPosition(sf::Vector2f cords)
{
	this->sprite.setPosition(cords);
}

sf::Vector2f Segment::getPosition()
{
	return this->sprite.getPosition();
}

sf::Sprite& Segment::getSprite()
{
	return this->sprite;
}

void Segment::setDirection(Direction dir)
{
	this->dir = dir;
}

Direction Segment::getDirection()
{
	return this->dir;
}