#pragma once
#include "Block.h"
#include "Snake.h"
#include "Food.h"
#include "Buff.h"
#include <vector>

class Board
{
public:
	Board();
	void draw(sf::RenderWindow&);
	void initialize(Snake&, Food&, bool&);
	void initialize(Snake&, Snake&, Food&, Food&, bool&);
	std::vector<Block>& getWall();

private:
	std::vector <Block> wall;
	sf::Sprite backgroundSprite;
};

