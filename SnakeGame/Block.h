#pragma once
#include <SFML/Graphics.hpp>
#include "Direction.h"

class Block
{
public:
	Block(sf::Texture&, int, int, Direction);
	Block(sf::Texture&, int, int);
	void updateAnimation();
	sf::Sprite& getSprite();

private:
	sf::Vector2u currentImage;
	sf::IntRect rect;
	sf::Sprite sprite;
};

