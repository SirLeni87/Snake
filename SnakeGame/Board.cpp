#include "Board.h"

using namespace sf;

Board::Board()
{
}

void Board::draw(RenderWindow& window)
{
	window.draw(this->backgroundSprite);
	
	for (Block b : this->wall)
	{
		window.draw(b.getRect());
	}
}

void Board::initialize(Snake& snake, Food& food, bool& loadingDone)
{
	for (int i = 0;; i++)
	{
		if (this->background.loadFromFile("resources/images/grass-background.jpg", IntRect(0, 0, 512, 512)))
		{
			break;
		}
		else if (i >= 4)
		{
			std::cout << "Could not load a texture!" << std::endl;
			exit(1);
		}
	}

	this->background.setRepeated(true);
	this->backgroundSprite.setTextureRect(IntRect(0, 0, 512, 512));
	this->backgroundSprite.setTexture(this->background);
	this->backgroundSprite.setPosition(0, 0);

	Texture* wallTexture = new Texture();
	for (int i = 0;; i++)
	{
		if (wallTexture->loadFromFile("resources/images/brick-wall-64x64.png"))
		{
			break;
		}
		else if (i >= 4)
		{
			std::cout << "Could not load a texture!" << std::endl;
			exit(1);
		}
	}

	Food::initialize();
	food.setTexture();

	Snake::initialize();
	snake.setTextures();

	for (int i = 0; i < 16; i++)
	{
		this->wall.push_back(Block(wallTexture, i * 32, 0));
		this->wall.push_back(Block(wallTexture, i * 32, 480));
	}
	for (int i = 1; i < 15; i++)
	{
		this->wall.push_back(Block(wallTexture, 0, i * 32));
		this->wall.push_back(Block(wallTexture, 480, i * 32));
	}

	loadingDone = true;
}

std::vector<Block> Board::getWall()
{
	return this->wall;
}
