#pragma once
#include "Block.h"
#include "Snake.h"
#include "Food.h"
#include "Buff.h"
#include <vector>

using namespace sf;

class Board
{
public:
	Board();
	void draw(sf::RenderWindow&);
	void initialize(Snake&, Food&, bool&);
	void initialize(Snake&, Snake&, Food&, Food&, Missle&, Missle&, bool&);
	std::vector<Block>& getWall();

private:
	std::vector <Block> wall;
	std::vector<Missle> missles;
	sf::Sprite backgroundSprite;
};

