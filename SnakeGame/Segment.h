#pragma once
#include "ResourceHolder.h"
#include "Direction.h"



class Segment
{
public:
	Segment();
	void setPosition(int, int);
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition();
	sf::Sprite& getSprite();
	void setDirection(Direction);
	Direction getDirection();
	static std::string dirToString(Direction);


protected:
	sf::Sprite sprite;
	Direction dir;
};

