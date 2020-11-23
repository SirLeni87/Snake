#include "Snake.h"


Snake::Snake(int x, int y)
{
	Segment segment;
	this->segments.push_back(segment);
	setPosition(x + 24, y + 24);
	this->dir = Direction::west;
}

void Snake::addSegment(bool second)
{
	Segment segment;
	if(!second)
		segment.getSprite().setTexture(ResourceHolder::loadTexture("segment"));
	else
		segment.getSprite().setTexture(ResourceHolder::loadTexture("segment2"));

	segment.getSprite().setOrigin(segment.getSprite().getLocalBounds().width / 2.f, segment.getSprite().getLocalBounds().height / 2.f);
	segment.setPosition(this->segments.back().getPosition());
	this->segments.push_back(segment);
}

void Snake::draw(sf::RenderWindow& window)
{
	window.draw(this->head.getSprite());
	for (Segment& s : this->segments)
	{
		window.draw(s.getSprite());
	}
	window.draw(this->tail.getSprite());

}

void Snake::setTextures(bool second)
{
	if (!second)
	{
		this->head.getSprite().setTexture(ResourceHolder::loadTexture("head"));
		this->segments[0].getSprite().setTexture(ResourceHolder::loadTexture("segment"));
		this->tail.getSprite().setTexture(ResourceHolder::loadTexture("tail"));

		this->head.getSprite().setOrigin(this->head.getSprite().getLocalBounds().width / 2.f, this->head.getSprite().getLocalBounds().height / 2.f);
		this->segments[0].getSprite().setOrigin(this->segments[0].getSprite().getLocalBounds().width / 2.f, this->segments[0].getSprite().getLocalBounds().height / 2.f);
		this->tail.getSprite().setOrigin(this->tail.getSprite().getLocalBounds().width / 2.f, this->tail.getSprite().getLocalBounds().height / 2.f);
	}
	else
	{
		this->head.getSprite().setTexture(ResourceHolder::loadTexture("head2"));
		this->segments[0].getSprite().setTexture(ResourceHolder::loadTexture("segment2"));
		this->tail.getSprite().setTexture(ResourceHolder::loadTexture("tail2"));

		this->head.getSprite().setOrigin(this->head.getSprite().getLocalBounds().width / 2.f, this->head.getSprite().getLocalBounds().height / 2.f);
		this->segments[0].getSprite().setOrigin(this->segments[0].getSprite().getLocalBounds().width / 2.f, this->segments[0].getSprite().getLocalBounds().height / 2.f);
		this->tail.getSprite().setOrigin(this->tail.getSprite().getLocalBounds().width / 2.f, this->tail.getSprite().getLocalBounds().height / 2.f);
	}
}

void Snake::updateTexture(bool second, bool afterSwap)
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

	for (Segment& s : this->segments)
	{
		if (s.getDirection() == Direction::north || s.getDirection() == Direction::south)
			s.getSprite().setRotation(90);
		else
			s.getSprite().setRotation(0);
	}

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

	if(!afterSwap)
		bend(second);
}

void Snake::setPosition(int x, int y)
{
	this->head.setPosition(x, y);
	this->segments[0].setPosition(x + 48, y);
	this->tail.setPosition(x + 96, y);
}

void Snake::setDirection(Direction dir)
{
	this->dir = dir;
}

Direction Snake::getDirection()
{
	return this->dir;
}

std::vector<Segment>& Snake::getSegmentList()
{
	return this->segments;
}

void Snake::move(bool& growth, bool second)
{
	if (growth)
	{
		addSegment(second);
	}

	int tempX = this->head.getPosition().x;
	int tempY = this->head.getPosition().y;
	Direction prevHeadDir = this->head.getDirection();
	Direction prevSegmentDir = this->segments.back().getDirection();
	sf::Vector2f prevSegmentPosition = this->segments.back().getPosition();

	switch (this->dir)
	{
	case Direction::north:
		this->head.setPosition(tempX, tempY - 48);
		break;
	case Direction::east:
		this->head.setPosition(tempX + 48, tempY);
		break;
	case Direction::south:
		this->head.setPosition(tempX, tempY + 48);
		break;
	case Direction::west:
		this->head.setPosition(tempX - 48, tempY);
		break;
	}
	this->head.setDirection(this->dir);
	for (int i = this->segments.size() - 1; i > 0; i--)
	{
		this->segments[i].setDirection(this->segments[i - 1].getDirection());
	}
	this->segments[0].setDirection(prevHeadDir);

	for (int i = this->segments.size() - 1; i > 0; i--)
	{
		this->segments[i].setPosition(this->segments[i - 1].getPosition());
	}
	this->segments[0].setPosition(tempX, tempY);

	if (!growth)
	{
		this->tail.setDirection(prevSegmentDir);
		this->tail.setPosition(prevSegmentPosition/*this->segments.back().getPosition().x, this->segments.back().getPosition().y*/);
	}
	growth = false;

	updateTexture(second);
}

void Snake::bend(bool second)
{
	if (this->head.getDirection() != this->segments[0].getDirection())
	{
		if(second)
			this->segments[0].getSprite().setTexture(ResourceHolder::loadTexture("bent-segment2"));
		else
			this->segments[0].getSprite().setTexture(ResourceHolder::loadTexture("bent-segment"));

		switch (this->segments[0].getDirection())
		{
		case Direction::north:
			if (this->head.getDirection() == Direction::east)
				this->segments[0].getSprite().setRotation(270);
			else
				this->segments[0].getSprite().setRotation(0);
			break;
		case Direction::east:
			if (this->head.getDirection() == Direction::north)
				this->segments[0].getSprite().setRotation(90);
			else
				this->segments[0].getSprite().setRotation(0);
			break;
		case Direction::south:
			if(this->head.getDirection() == Direction::east)
				this->segments[0].getSprite().setRotation(180);
			else
				this->segments[0].getSprite().setRotation(90);
			break;
		case Direction::west:
			if (this->head.getDirection() == Direction::north)
				this->segments[0].getSprite().setRotation(180);
			else
				this->segments[0].getSprite().setRotation(270);
			break;
		}
	}
	else
	{
		if(second)
			this->segments[0].getSprite().setTexture(ResourceHolder::loadTexture("segment2"));
		else
			this->segments[0].getSprite().setTexture(ResourceHolder::loadTexture("segment"));
	}

	for (int i = 1; i < this->segments.size(); i++)
	{
		if (this->segments[i - 1].getDirection() != this->segments[i].getDirection())
		{
			if(second)
				this->segments[i].getSprite().setTexture(ResourceHolder::loadTexture("bent-segment2"));
			else
				this->segments[i].getSprite().setTexture(ResourceHolder::loadTexture("bent-segment"));

			switch (this->segments[i].getDirection())
			{
			case Direction::north:
				if (this->segments[i - 1].getDirection() == Direction::east)
					this->segments[i].getSprite().setRotation(270);
				else
					this->segments[i].getSprite().setRotation(0);
				break;
			case Direction::east:
				if (this->segments[i - 1].getDirection() == Direction::north)
					this->segments[i].getSprite().setRotation(90);
				else
					this->segments[i].getSprite().setRotation(0);
				break;
			case Direction::south:
				if (this->segments[i - 1].getDirection() == Direction::east)
					this->segments[i].getSprite().setRotation(180);
				else
					this->segments[i].getSprite().setRotation(90);
				break;
			case Direction::west:
				if (this->segments[i - 1].getDirection() == Direction::north)
					this->segments[i].getSprite().setRotation(180);
				else
					this->segments[i].getSprite().setRotation(270);
				break;
			}
		}
		else
		{
			if(second)
				this->segments[i].getSprite().setTexture(ResourceHolder::loadTexture("segment2"));
			else
				this->segments[i].getSprite().setTexture(ResourceHolder::loadTexture("segment"));
		}
	}

	if (this->segments.back().getDirection() != this->tail.getDirection())
	{

		switch (this->tail.getDirection())
		{
		case Direction::north:
			if (this->segments.back().getDirection() == Direction::east)
			{
				if(second)
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail4"));
				else
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail2"));
				
				this->tail.getSprite().setRotation(0);
			}
			else
			{
				if (second)
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail3"));
				else
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail"));

				this->tail.getSprite().setRotation(0);
			}
			break;
		case Direction::east:
			if (this->segments.back().getDirection() == Direction::north)
			{
				if (second)
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail3"));
				else
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail"));

				this->tail.getSprite().setRotation(90);
			}
			else
			{
				if (second)
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail4"));
				else
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail2"));

				this->tail.getSprite().setRotation(90);
			}
			break;
		case Direction::south:
			if (this->segments.back().getDirection() == Direction::east)
			{
				if (second)
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail3"));
				else
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail"));

				this->tail.getSprite().setRotation(180);
			}
			else
			{
				if (second)
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail4"));
				else
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail2"));

				this->tail.getSprite().setRotation(180);
			}
			break;
		case Direction::west:
			if (this->segments.back().getDirection() == Direction::north)
			{
				if (second)
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail4"));
				else
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail2"));

				this->tail.getSprite().setRotation(270);
			}
			else
			{
				if (second)
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail3"));
				else
					this->tail.getSprite().setTexture(ResourceHolder::loadTexture("bent-tail"));

				this->tail.getSprite().setRotation(270);
			}
			break;
		}
	}
	else
	{
		if(second)
			this->tail.getSprite().setTexture(ResourceHolder::loadTexture("tail2"));
		else
			this->tail.getSprite().setTexture(ResourceHolder::loadTexture("tail"));
	}
}

bool Snake::isCollided()
{
	for (Segment s : this->segments)
	{
		if (this->head.getPosition() == s.getPosition())
			return true;
	}
	if (this->head.getPosition() == this->tail.getPosition())
		return true;

	return false;
}

void Snake::setElusiveness()
{
	this->elusive = true;

	std::thread elusiveCountdown([this]() {
		Clock clock;
		Clock flickerClock;
		bool transparent = false;
		while (1)
		{
			if (clock.getElapsedTime().asSeconds() > 3)
			{

				if (flickerClock.getElapsedTime().asSeconds() > 0.2)
				{
					if (!transparent)
					{
						this->head.getSprite().setColor(Color(255,255,255,128));
						for (Segment& s : this->segments)
						{
							s.getSprite().setColor(Color(255, 255, 255, 128));
						}
						this->tail.getSprite().setColor(Color(255,255,255,128));
						transparent = true;
					}
					else
					{
						this->head.getSprite().setColor(Color(255, 255, 255, 255));
						for (Segment& s : this->segments)
						{
							s.getSprite().setColor(Color(255, 255, 255, 255));
						}
						this->tail.getSprite().setColor(Color(255, 255, 255, 255));
						transparent = false;
					}
					flickerClock.restart();
				}
			}
			if (clock.getElapsedTime().asSeconds() > 5)
			{
				this->head.getSprite().setColor(Color(255, 255, 255, 255));
				for (Segment& s : this->segments)
				{
					s.getSprite().setColor(Color(255, 255, 255, 255));
				}
				this->tail.getSprite().setColor(Color(255, 255, 255, 255));
				elusive = false;
				break;
			}
		}
		});
	elusiveCountdown.detach();
}

bool Snake::isElusive()
{
	return this->elusive;
}

void Snake::setStunned()
{
	this->stunned = true;

	std::thread stunCountdown([this]() {
		Clock clock;
		while (1)
		{
			if (clock.getElapsedTime().asSeconds() > 2)
			{
				stunned = false;
				break;
			}
		}
		});
	stunCountdown.detach();
}

bool Snake::isStunned()
{
	return this->stunned;
}

void Snake::setMissle(bool set)
{
	this->missleUp = set;
}

bool Snake::hasMissle()
{
	return this->missleUp;
}

void Snake::afterSwap(bool second)
{
	Direction savedDir = this->dir;
	this->head.setDirection(savedDir);

	switch (savedDir)
	{
	case Direction::north:
		this->segments[0].setPosition(this->head.getPosition().x, this->head.getPosition().y + 48);
		this->tail.setPosition(this->segments[0].getPosition().x, this->segments[0].getPosition().y + 48);
		break;
	case Direction::east:
		this->segments[0].setPosition(this->head.getPosition().x - 48, this->head.getPosition().y);
		this->tail.setPosition(this->segments[0].getPosition().x - 48, this->segments[0].getPosition().y);
		break;
	case Direction::south:
		this->segments[0].setPosition(this->head.getPosition().x, this->head.getPosition().y - 48);
		this->tail.setPosition(this->segments[0].getPosition().x, this->segments[0].getPosition().y - 48);
		break;
	case Direction::west:
		this->segments[0].setPosition(this->head.getPosition().x + 48, this->head.getPosition().y);
		this->tail.setPosition(this->segments[0].getPosition().x + 48, this->segments[0].getPosition().y);
		break;
	}

	this->segments[0].setDirection(savedDir);
	if(second)
		this->segments[0].getSprite().setTexture(ResourceHolder::loadTexture("segment2"));
	else
		this->segments[0].getSprite().setTexture(ResourceHolder::loadTexture("segment"));

	for (int i = 1; i < this->segments.size(); i++)
	{
		if(second)
			this->segments[i].getSprite().setTexture(ResourceHolder::loadTexture("segment2"));
		else
			this->segments[i].getSprite().setTexture(ResourceHolder::loadTexture("segment"));

		this->segments[i].setPosition(this->segments[0].getPosition());
		this->segments[i].setDirection(savedDir);
	}
	if(second)
		this->tail.getSprite().setTexture(ResourceHolder::loadTexture("tail2"));
	else
		this->tail.getSprite().setTexture(ResourceHolder::loadTexture("tail"));

	this->tail.setDirection(savedDir);

	updateTexture(second, true);
}

sf::Vector2f Snake::getPosition()
{
	return this->head.getPosition();
}
