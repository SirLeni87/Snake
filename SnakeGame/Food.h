#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>
#include <iostream>

class Food
{
public:
	Food();
	void newPosition();
	static void initialize();
	void setTexture();
	sf::Vector2f getPosition();
	void draw(sf::RenderWindow&);

private:
	sf::Sprite sprite;
	static sf::Texture* texture;
};

