#include "Snake.h"

using namespace sf;

Snake::Snake(int x, int y)
{
	setPosition(x + 16, y + 16);
	this->dir = Direction::west;

	//this->head = new Head(x, y);
	//this->segment = new Segment(x + 16, y);
	//this->tail = new Tail(x + 32, y);
}

void Snake::initialize()
{
	Segment::setSegmentTexture("body-temp.png");
	Head::setSegmentTexture("head-temp.png");
	Tail::setSegmentTexture("tail-temp.png");
}

void Snake::draw(sf::RenderWindow& window)
{
	window.draw(this->head.getSprite());
	window.draw(this->segment.getSprite());
	window.draw(this->tail.getSprite());

}

void Snake::setTextures()
{
	this->head.getSprite().setTexture(Head::getTexture());
	this->segment.getSprite().setTexture(Segment::getTexture());
	this->tail.getSprite().setTexture(Tail::getTexture());

	this->head.getSprite().setScale(0.5, 0.5);
	this->segment.getSprite().setScale(0.5, 0.5);
	this->tail.getSprite().setScale(0.5, 0.5);

	this->head.getSprite().setOrigin(this->head.getSprite().getLocalBounds().width / 2.f, this->head.getSprite().getLocalBounds().height / 2.f);
	this->segment.getSprite().setOrigin(this->segment.getSprite().getLocalBounds().width / 2.f, this->segment.getSprite().getLocalBounds().height / 2.f);
	this->tail.getSprite().setOrigin(this->tail.getSprite().getLocalBounds().width / 2.f, this->tail.getSprite().getLocalBounds().height / 2.f);
}

void Snake::updateTexture()
{
	switch (this->head.getDirection())
	{
	case Direction::north:
		this->head.getSprite().setRotation(90);
		break;
	case Direction::east:
		this->head.getSprite().setRotation(180);
		break;
	case Direction::south:
		this->head.getSprite().setRotation(270);
		break;
	case Direction::west:
		this->head.getSprite().setRotation(0);
		break;
	}

	if (this->segment.getDirection() == Direction::north || this->segment.getDirection() == Direction::south)
		this->segment.getSprite().setRotation(90);
	else
		this->segment.getSprite().setRotation(0);

	switch (this->tail.getDirection())
	{
	case Direction::north:
		this->tail.getSprite().setRotation(90);
		break;
	case Direction::east:
		this->tail.getSprite().setRotation(180);
		break;
	case Direction::south:
		this->tail.getSprite().setRotation(270);
		break;
	case Direction::west:
		this->tail.getSprite().setRotation(0);
		break;
	}
}

void Snake::setPosition(int x, int y)
{
	this->head.setPosition(x, y);
	this->segment.setPosition(x + 32, y);
	this->tail.setPosition(x + 64, y);
}

void Snake::setDirection(Direction dir)
{
	this->dir = dir;
}

Direction Snake::getDirection()
{
	return this->dir;
}

void Snake::move()
{

	int tempX = this->head.getPosition().x;
	int tempY = this->head.getPosition().y;
	Direction prevHeadDir = this->head.getDirection();
	Direction prevSegmentDir = this->segment.getDirection();

	switch (this->dir)
	{
	case Direction::north:
		this->head.setPosition(tempX, tempY - 32);
		break;
	case Direction::east:
		this->head.setPosition(tempX + 32, tempY);
		break;
	case Direction::south:
		this->head.setPosition(tempX, tempY + 32);
		break;
	case Direction::west:
		this->head.setPosition(tempX - 32, tempY);
		break;
	}
	this->head.setDirection(this->dir);
	this->segment.setDirection(prevHeadDir);
	this->tail.setDirection(prevSegmentDir);

	this->tail.setPosition(this->segment.getPosition().x, this->segment.getPosition().y);
	this->segment.setPosition(tempX, tempY);

	updateTexture();
}

sf::Vector2f Snake::getPosition()
{
	return this->head.getPosition();
}
