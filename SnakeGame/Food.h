#pragma once
#include <time.h>
#include <stdlib.h>
#include "ResourceHolder.h"

class Food
{
public:
	Food(bool = false);
	void newPosition(bool = false);
	void setPosition(sf::Vector2f);
	void setTexture(std::string);
	sf::Vector2f getPosition();
	sf::Sprite& getSprite();
	void draw(sf::RenderWindow&);
	void animate();

protected:
	int animationOffsets[20] = {0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -4, -3, -2, -1};
	int currentOffsetIndex = 0;

	sf::Sprite sprite;
	sf::Vector2f position;
};

