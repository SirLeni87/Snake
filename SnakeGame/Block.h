#pragma once
#include <SFML/Graphics.hpp>

class Block
{
public:
	Block(sf::Texture&, int, int);
	sf::Sprite& getSprite();

private:
	sf::Sprite sprite;
};

