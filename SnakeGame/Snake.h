#pragma once
#include <iostream>
#include "Segment.h"
#include <vector>
#include <thread>


class Snake
{
public:
	Snake(int, int);
	void addSegment();
	void draw(sf::RenderWindow&);
	void setTextures();
	void updateTexture();
	void setPosition(int, int);
	sf::Vector2f getPosition();
	void setDirection(Direction);
	Direction getDirection();
	std::vector<Segment>& getSegmentList();
	void move(bool&);
	void bend();
	bool isCollided();
	void setElusiveness();
	bool isElusive();
	void afterSwap();

private:
	Segment head;
	std::vector<Segment> segments;
	Segment tail;
	Direction dir;
	bool elusive = false;
};

