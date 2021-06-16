#include "Block.h"

Block::Block(sf::Texture& texture, int x, int y, Direction dir)
{
	rect.width = 64;
	rect.height = 64;
	currentImage = sf::Vector2u(0,0);
	this->sprite.setTexture(texture);
	this->sprite.setScale(0.75, 0.75);
	this->sprite.setPosition(x, y);
	this->sprite.setOrigin(this->sprite.getLocalBounds().width / 8.f, this->sprite.getLocalBounds().height / 2.f);

	switch (dir)
	{
	case Direction::east:
		this->sprite.setRotation(90);
		break;
	case Direction::south:
		this->sprite.setRotation(180);
		break;
	case Direction::west:
		this->sprite.setRotation(270);
		break;
	default:
		break;
	}

	sprite.setTextureRect(rect);
}

Block::Block(sf::Texture& texture, int x, int y)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(0.75, 0.75);
	this->sprite.setPosition(x, y);
	this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2.f, this->sprite.getLocalBounds().height / 2.f);
}

void Block::updateAnimation()
{
	currentImage.x = (currentImage.x + 1) % 4;
	rect.left = currentImage.x * rect.width;
	
	sprite.setTextureRect(rect);
}

sf::Sprite& Block::getSprite()
{
	return this->sprite;
}