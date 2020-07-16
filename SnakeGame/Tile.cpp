#include "Tile.h"

Tile::Tile(Texture* texture, int x, int y)
{
	RectangleShape tileRect(Vector2f(8,8));
	tileRect.setTexture(texture);
	tileRect.setPosition(x, y);
}
