#pragma once
#include <iostream>
#include "Head.h"
#include "Tail.h"


class Snake
{
public:
	Snake(int, int);
	static void initialize();
	void draw(sf::RenderWindow&);
	void setTextures();
	void updateTexture();
	void setPosition(int, int);
	sf::Vector2f getPosition();
	void setDirection(Direction);
	Direction getDirection();
	void move();

private:
	Head head;
	Segment segment;
	Tail tail;
	Direction dir;
};

