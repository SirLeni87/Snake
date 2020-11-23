#pragma once
#include "Segment.h"

class Missle
{
public:
	Missle(int, int);
	void setPosition(sf::Vector2f, Direction);
	void move();
	void setTexture(std::string);
	sf::Sprite& getSprite();

private:
	sf::Sprite sprite;
	Direction dir;
};

