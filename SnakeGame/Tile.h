#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;

class Tile
{
public:
	Tile(Texture*, int, int);
	static Texture loadGridTexture(std::string);

private:
	bool isPassable;
	Texture texture;
};

