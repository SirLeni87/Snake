#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Block
{
public:
	Block(Texture*, int, int);
	RectangleShape getRect();

private:
	RectangleShape rect;
};

