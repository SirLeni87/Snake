#include "Grid.h"

Grid::Grid(RenderTexture* texture, int x, int y)
{
	this->x = x / 8;
	this->y = y / 8;
	this->texture = texture;
}
