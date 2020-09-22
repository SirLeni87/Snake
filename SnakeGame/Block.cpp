#include "Block.h"

Block::Block(sf::Texture& texture, int x, int y)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(0.75, 0.75);
	this->sprite.setPosition(x, y);
	this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2.f, this->sprite.getLocalBounds().height / 2.f);
}

sf::Sprite& Block::getSprite()
{
	return this->sprite;
}