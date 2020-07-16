#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Grid
{
public:
	Grid(RenderTexture* texture, int x, int y);

private:
	unsigned int x;
	unsigned int y;
	RenderTexture* texture;

};

