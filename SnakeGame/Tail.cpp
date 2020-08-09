#include "Tail.h"

sf::Texture* Tail::texture;

Tail::Tail() : Segment()
{
}

sf::Texture& Tail::getTexture()
{
	return *(Tail::texture);
}

void Tail::setSegmentTexture(std::string file)
{
	texture = new sf::Texture();
	for (int i = 0;; i++)
	{
		if (texture->loadFromFile("resources/images/" + file))
		{
			break;
		}
		else if (i >= 4)
		{
			std::cout << "Could not load a texture!" << std::endl;
			exit(1);
		}
	}
}