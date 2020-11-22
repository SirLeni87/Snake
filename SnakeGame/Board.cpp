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
		window.draw(b.getSprite());
	}
}

void Board::initialize(Snake& snake, Food& food, bool& loadingDone)
{
	this->backgroundSprite.setTexture(ResourceHolder::loadTexture("background"));
	this->backgroundSprite.setPosition(0, 0);

	food.setTexture("fish1");

	snake.setTextures();

	for (int i = 1; i < 15; i++)
	{
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-down"), i * 48 + 24, 0 + 24));
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-up"), i * 48 + 24, 720 + 24));
	}
	for (int i = 1; i < 15; i++)
	{
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-right"), 0 + 24, i * 48 + 24));
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-left"), 720 + 24, i * 48 + 24));
	}

	Block corner1(ResourceHolder::loadTexture("algae-corner"), 0 + 24, 720 + 24);
	Block corner2(ResourceHolder::loadTexture("algae-corner"), 0 + 24, 0 + 24);
	corner2.getSprite().setRotation(90);
	Block corner3(ResourceHolder::loadTexture("algae-corner"), 720 + 24, 0 + 24);
	corner3.getSprite().setRotation(180);
	Block corner4(ResourceHolder::loadTexture("algae-corner"), 720 + 24, 720 + 24);
	corner4.getSprite().setRotation(270);

	this->wall.push_back(corner1);
	this->wall.push_back(corner2);
	this->wall.push_back(corner3);
	this->wall.push_back(corner4);

	loadingDone = true;
}

void Board::initialize(Snake& snake, Snake& snake2, Food& food, Food& food2, Missle& missle1, Missle& missle2, bool& loadingDone)
{
	ResourceHolder::loadTexture("background").setRepeated(true);
	this->backgroundSprite.setTextureRect(IntRect(0,0, 1536, 768));
	this->backgroundSprite.setTexture(ResourceHolder::loadTexture("background"));
	this->backgroundSprite.setPosition(0, 0);

	food.setTexture("fish1");
	food2.setTexture("fish2");

	missle1.setTexture("shell");
	missle2.setTexture("shell");

	snake.setTextures();
	snake2.setTextures(true);

	for (int i = 1; i < 31; i++)
	{
		if (i == 15 || i == 16)
			continue;
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-down"), i * 48 + 24, 0 + 24));
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-up"), i * 48 + 24, 720 + 24));
	}
	for (int i = 1; i < 15; i++)
	{
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-right"), 0 + 24, i * 48 + 24));
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-left"), 720 + 24, i * 48 + 24));
	}
	for (int i = 1; i < 15; i++)
	{
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-right"), 768 + 24, i * 48 + 24));
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-left"), 1488 + 24, i * 48 + 24));
	}

	for (int i = 0; i < 2; i++)
	{
		Block corner1(ResourceHolder::loadTexture("algae-corner"), 0 + i * 768 + 24, 720 + 24);
		Block corner2(ResourceHolder::loadTexture("algae-corner"), 0 + i * 768 + 24, 0 + 24);
		corner2.getSprite().setRotation(90);
		Block corner3(ResourceHolder::loadTexture("algae-corner"), 720 + i * 768 + 24, 0 + 24);
		corner3.getSprite().setRotation(180);
		Block corner4(ResourceHolder::loadTexture("algae-corner"), 720 + i * 768 + 24, 720 + 24);
		corner4.getSprite().setRotation(270);

		this->wall.push_back(corner1);
		this->wall.push_back(corner2);
		this->wall.push_back(corner3);
		this->wall.push_back(corner4);
	}

	loadingDone = true;
}

std::vector<Block>& Board::getWall()
{
	return this->wall;
}
