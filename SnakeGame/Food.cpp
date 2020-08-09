#include "Food.h"

sf::Texture* Food::texture;

Food::Food()
{
	newPosition();
}

void Food::newPosition()
{
	srand(time(NULL));

	int x = ((rand() % 14 + 1) * 32) + 16;
	int y = ((rand() % 14 + 1) * 32) + 16;

	this->sprite.setPosition(x,y);
}

void Food::initialize()
{
	texture = new sf::Texture;

	for (int i = 0;; i++)
	{
		if (texture->loadFromFile("resources/images/fruit-temp.png"))
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

void Food::setTexture()
{
	this->sprite.setTexture(*texture);
	this->sprite.setScale(0.5, 0.5);

	this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2.f, this->sprite.getLocalBounds().height / 2.f);
}

sf::Vector2f Food::getPosition()
{
	return this->sprite.getPosition();
}

void Food::draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}
