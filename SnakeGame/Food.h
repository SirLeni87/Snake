#pragma once
#include <time.h>
#include <stdlib.h>
#include "ResourceHolder.h"

class Food
{
public:
	Food(bool = false);
	void newPosition(bool = false);
	void setTexture(std::string);
	sf::Vector2f getPosition();
	sf::Sprite&
		getSprite();
	void draw(sf::RenderWindow&);

protected:
	sf::Sprite sprite;
};

