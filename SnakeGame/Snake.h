#pragma once
#include <iostream>
#include "Missle.h"
#include <vector>
#include <thread>


class Snake
{
public:
	Snake(int, int);
	void addSegment(bool = false);
	void draw(sf::RenderWindow&);
	void setTextures(bool = false);
	void updateTexture(bool = false, bool = false);
	void setPosition(int, int);
	sf::Vector2f getPosition();
	void setDirection(Direction);
	Direction getDirection();
	std::vector<Segment>& getSegmentList();
	void move(bool&, bool = false);
	void bend(bool = false);
	bool isCollided();
	void setElusiveness();
	bool isElusive();
	void setStunned();
	bool isStunned();
	void setMissle(bool);
	bool hasMissle();
	void afterSwap(bool = false);

private:
	Segment head;
	std::vector<Segment> segments;
	Segment tail;
	Direction dir;
	bool elusive = false;
	bool stunned = false;
	bool missleUp = false;
	bool justShot = true;
};

