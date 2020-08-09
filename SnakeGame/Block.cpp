#include "Block.h"

Block::Block(Texture* texture, int x, int y)
{
	this->rect.setSize(Vector2f(32, 32));
	this->rect.setTexture(texture);
	this->rect.setPosition(x + 16, y + 16);
	this->rect.setOrigin(this->rect.getLocalBounds().width / 2.f, this->rect.getLocalBounds().height / 2.f);
}

RectangleShape Block::getRect()
{
	return this->rect;
}