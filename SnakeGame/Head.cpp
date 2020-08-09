#include "Head.h"

sf::Texture* Head::texture;

Head::Head() : Segment()
{
}

sf::Texture& Head::getTexture()
{
	return *(Head::texture);
}

void Head::setSegmentTexture(std::string file)
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
