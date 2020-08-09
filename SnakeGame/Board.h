#pragma once
#include "Block.h"
#include "Snake.h"
#include "Food.h"
#include <vector>

class Board
{
public:
	Board();
	void draw(sf::RenderWindow&);
	void initialize(Snake&, Food&, bool&);
	std::vector<Block> getWall();

private:
	std::vector <Block> wall;
	sf::Sprite backgroundSprite;
	sf::Texture background;
};

