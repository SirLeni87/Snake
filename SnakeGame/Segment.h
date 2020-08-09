#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>


enum class Direction
{
	north,
	east,
	south,
	west
};

class Segment
{
public:
	Segment();
	void setPosition(int, int);
	sf::Vector2f getPosition();
	static sf::Texture& getTexture();
	static void setSegmentTexture(std::string);
	sf::Sprite& getSprite();
	void setDirection(Direction);
	Direction getDirection();


protected:
	sf::Sprite sprite;
	static sf::Texture* texture;
	Direction dir;
};

