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
	ResourceHolder::insertTexture("background", "resources/images/background-water.png");
	ResourceHolder::insertTexture("algae-up", "resources/images/algae-up.png");
	ResourceHolder::insertTexture("algae-left", "resources/images/algae-left.png");
	ResourceHolder::insertTexture("algae-right", "resources/images/algae-right.png");
	ResourceHolder::insertTexture("algae-down", "resources/images/algae-down.png");
	ResourceHolder::insertTexture("algae-corner", "resources/images/algae-corner.png");
	ResourceHolder::insertTexture("head", "resources/images/head.png");
	ResourceHolder::insertTexture("segment", "resources/images/segment.png");
	ResourceHolder::insertTexture("bent-segment", "resources/images/bent-segment.png");
	ResourceHolder::insertTexture("tail", "resources/images/tail.png");
	ResourceHolder::insertTexture("bent-tail", "resources/images/tail-bent1.png");
	ResourceHolder::insertTexture("bent-tail2", "resources/images/tail-bent2.png");
	ResourceHolder::insertTexture("fish1", "resources/images/fish1.png");


	this->backgroundSprite.setTexture(ResourceHolder::loadTexture("background"));
	this->backgroundSprite.setPosition(0, 0);

	food.setTexture("fish1");

	snake.setTextures();

	for (int i = 1; i < 15; i++)
	{
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-down"), i * 32, 0));
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-up"), i * 32, 480));
	}
	for (int i = 1; i < 15; i++)
	{
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-right"), 0, i * 32));
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-left"), 480, i * 32));
	}

	Block corner1(ResourceHolder::loadTexture("algae-corner"), 0, 480);
	Block corner2(ResourceHolder::loadTexture("algae-corner"), 0, 0);
	corner2.getSprite().setRotation(90);
	Block corner3(ResourceHolder::loadTexture("algae-corner"), 480, 0);
	corner3.getSprite().setRotation(180);
	Block corner4(ResourceHolder::loadTexture("algae-corner"), 480, 480);
	corner4.getSprite().setRotation(270);

	this->wall.push_back(corner1);
	this->wall.push_back(corner2);
	this->wall.push_back(corner3);
	this->wall.push_back(corner4);

	loadingDone = true;
}

void Board::initialize(Snake& snake, Snake& snake2, Food& food, Food& food2, bool& loadingDone)
{
	ResourceHolder::insertTexture("background", "resources/images/background-water.png");
	ResourceHolder::insertTexture("algae-up", "resources/images/algae-up.png");
	ResourceHolder::insertTexture("algae-left", "resources/images/algae-left.png");
	ResourceHolder::insertTexture("algae-right", "resources/images/algae-right.png");
	ResourceHolder::insertTexture("algae-down", "resources/images/algae-down.png");
	ResourceHolder::insertTexture("algae-corner", "resources/images/algae-corner.png");
	ResourceHolder::insertTexture("head", "resources/images/head.png");
	ResourceHolder::insertTexture("segment", "resources/images/segment.png");
	ResourceHolder::insertTexture("bent-segment", "resources/images/bent-segment.png");
	ResourceHolder::insertTexture("tail", "resources/images/tail.png");
	ResourceHolder::insertTexture("bent-tail", "resources/images/tail-bent1.png");
	ResourceHolder::insertTexture("bent-tail2", "resources/images/tail-bent2.png");
	ResourceHolder::insertTexture("fish1", "resources/images/fish1.png");
	ResourceHolder::insertTexture("fish2", "resources/images/fish2.png");
	ResourceHolder::insertTexture("nautilus", "resources/images/nautilus.png");
	ResourceHolder::insertTexture("shrimp", "resources/images/shrimp.png");
	ResourceHolder::insertTexture("pufferfish", "resources/images/pufferfish.png");
	ResourceHolder::insertTexture("jellyfish", "resources/images/jellyfish.png");
	ResourceHolder::insertTexture("whirlpool", "resources/images/whirlpool.png");

	ResourceHolder::loadTexture("background").setRepeated(true);
	this->backgroundSprite.setTextureRect(IntRect(0,0,1024,512));
	this->backgroundSprite.setTexture(ResourceHolder::loadTexture("background"));
	this->backgroundSprite.setPosition(0, 0);

	food.setTexture("fish1");
	food2.setTexture("fish2");

	snake.setTextures();
	snake2.setTextures();

	for (int i = 1; i < 31; i++)
	{
		if (i == 15 || i == 16)
			continue;
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-down"), i * 32 + 16, 0 + 16));
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-up"), i * 32 + 16, 480 + 16));
	}
	for (int i = 1; i < 15; i++)
	{
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-right"), 0 + 16, i * 32 + 16));
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-left"), 480 + 16, i * 32 + 16));
	}
	for (int i = 1; i < 15; i++)
	{
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-right"), 512 + 16, i * 32 + 16));
		this->wall.push_back(Block(ResourceHolder::loadTexture("algae-left"), 992 + 16, i * 32 + 16));
	}

	for (int i = 0; i < 2; i++)
	{
		Block corner1(ResourceHolder::loadTexture("algae-corner"), 0 + i * 512 + 16, 480 + 16);
		Block corner2(ResourceHolder::loadTexture("algae-corner"), 0 + i * 512 + 16, 0 + 16);
		corner2.getSprite().setRotation(90);
		Block corner3(ResourceHolder::loadTexture("algae-corner"), 480 + i * 512 + 16, 0 + 16);
		corner3.getSprite().setRotation(180);
		Block corner4(ResourceHolder::loadTexture("algae-corner"), 480 + i * 512 + 16, 480 + 16);
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
