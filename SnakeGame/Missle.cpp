#include "Missle.h"

Missle::Missle(int x, int y)
{
	this->sprite.setPosition(x,y);
	this->dir = Direction::west;
}

void Missle::setPosition(sf::Vector2f position, Direction direction)
{
	switch (direction)
	{
	case Direction::north:
		this->dir = direction;
		this->sprite.setPosition(position.x, position.y - 48);
		break;
	case Direction::east:
		this->dir = direction;
		this->sprite.setPosition(position.x + 48, position.y);
		break;
	case Direction::south:
		this->dir = direction;
		this->sprite.setPosition(position.x, position.y + 48);
		break;
	case Direction::west:
		this->dir = direction;
		this->sprite.setPosition(position.x - 48, position.y);
		break;
	}
}

void Missle::move()
{
	switch (this->dir)
	{
	case Direction::north:
		this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - 48);
		break;
	case Direction::east:
		this->sprite.setPosition(this->sprite.getPosition().x + 48, this->sprite.getPosition().y);
		break;
	case Direction::south:
		this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y + 48);
		break;
	case Direction::west:
		this->sprite.setPosition(this->sprite.getPosition().x - 48, this->sprite.getPosition().y);
		break;
	}
}

void Missle::setTexture(std::string texture)
{
	this->sprite.setTexture(ResourceHolder::loadTexture(texture));
	this->sprite.setScale(0.75, 0.75);
	this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2.f, this->sprite.getLocalBounds().height / 2.f);
}

sf::Sprite& Missle::getSprite()
{
	return this->sprite;
}