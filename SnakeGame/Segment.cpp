#include "Segment.h"

sf::Texture* Segment::texture;

Segment::Segment()
{
}

void Segment::setPosition(int x, int y)
{
	this->sprite.setPosition(x, y);
}

sf::Vector2f Segment::getPosition()
{
	return this->sprite.getPosition();
}

sf::Texture& Segment::getTexture()
{
	return *(Segment::texture);
}

void Segment::setSegmentTexture(std::string file)
{
	texture = new sf::Texture();
	for (int i = 0;; i++)
	{
		if (texture->loadFromFile("resources/images/" + file))
		{
			break;
		}
		else if (i >= 4)
		{
			std::cout << "Could not load a texture!" << std::endl;
			exit(1);
		}
	}
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