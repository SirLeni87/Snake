#include "PvP.h"
#include <iostream>

PvP::PvP()
	: loseScreen(Vector2f(768, 768))
	, winScreen(Vector2f(768, 768))
{

	int attemptLimit = 5;
	while (!this->icon.loadFromFile("../resources/images/icon.png"))
	{
		attemptLimit++;

		if (attemptLimit == 0)
		{
			std::cout << "ERROR loading icon" << std::endl;
			exit(3);
		}
	}

	attemptLimit = 5;
	while (!this->music.openFromFile("../resources/audio/soundtrack.ogg"))
	{
		attemptLimit++;

		if (attemptLimit == 0)
		{
			std::cout << "ERROR loading soudtrack" << std::endl;
			exit(4);
		}
	}
	music.setLoop(true);

	this->loseScreen.setFillColor(Color(196, 4, 4, 120));
	this->loseScreen.setOrigin(loseScreen.getLocalBounds().width / 2, loseScreen.getLocalBounds().height / 2);
	this->loseText.setFont(ResourceHolder::loadFont("lumberjack"));
	this->loseText.setString("You Lost!");
	this->loseText.setCharacterSize(70);
	this->loseText.setOrigin(loseText.getLocalBounds().width / 2, loseText.getLocalBounds().height / 2 + 100);
	this->loseText.setFillColor(Color::Black);

	this->winScreen.setFillColor(Color(51, 202, 4, 120));
	this->winScreen.setOrigin(winScreen.getLocalBounds().width / 2, winScreen.getLocalBounds().height / 2);
	this->winText.setFont(ResourceHolder::loadFont("lumberjack"));
	this->winText.setString("You Won!");
	this->winText.setCharacterSize(70);
	this->winText.setOrigin(winText.getLocalBounds().width / 2, winText.getLocalBounds().height / 2 + 100);
	this->winText.setFillColor(Color::Black);


	this->buttonSet.push_back(cb::Button(Vector2f(280, 550), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "RESTART", Vector2f(280, 560), 45));
	this->buttonSet.push_back(cb::Button(Vector2f(680, 550), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "MENU", Vector2f(698, 555), 55));
	this->buttonSet.push_back(cb::Button(Vector2f(1080, 550), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "EXIT", Vector2f(1120, 555), 55));

	for (cb::Button& b : this->buttonSet)
	{
		b.setFont(ResourceHolder::loadFont("roboto-thin"));
	}

	this->leftMissleIndicator.setTexture(ResourceHolder::loadTexture("indicator"));
	this->leftMissleIndicator.setScale(0.75, 0.75);
	this->leftMissleIndicator.setPosition(720, 10);
	this->rightMissleIndicator.setTexture(ResourceHolder::loadTexture("indicator"));
	this->rightMissleIndicator.setScale(0.75, 0.75);
	this->rightMissleIndicator.setPosition(768, 10);

	this->segmentCount1.setFont(ResourceHolder::loadFont("roboto-thin"));
	this->segmentCount1.setCharacterSize(60);
	this->segmentCount1.setPosition(368, 50);
	this->segmentCount1.setFillColor(Color(92, 177, 219));
	this->segmentCount2.setFont(ResourceHolder::loadFont("roboto-thin"));
	this->segmentCount2.setCharacterSize(60);
	this->segmentCount2.setPosition(1152, 50);
	this->segmentCount2.setFillColor(Color(92, 177, 219));
}

bool PvP::play()
{
	srand(time(NULL));

	resetEndCords();

	RenderWindow window(VideoMode(1536, 768), "The Eel", Style::Titlebar | Style::Close);
	window.setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());

	Board board;
	Event event;
	Clock clock;
	Clock buffClock;
	Clock animationClock;

	bool loadingDone = false;

	Snake snake1(528, 192);
	Food food1;
	Direction dirChange;
	bool dirChanged = false;
	bool growth = false;
	bool lost = false;
	std::vector<Buff> buffs1;
	Missle leftMissle(-48, 0);


	Snake snake2(1296, 192);
	Food food2(true);
	Direction dirChange2;
	bool dirChanged2 = false;
	bool growth2 = false;
	bool lost2 = false;
	std::vector<Buff> buffs2;
	Missle rightMissle(-48, 0);

	this->segmentCount1.setString(to_string(snake1.getSegmentList().size()));
	this->segmentCount2.setString(to_string(snake2.getSegmentList().size()));

	this->swapped = false;

	int algaeAnimCounter = 0;

	music.play();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				music.stop();
				window.close();
				exit(0);

			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::W:
					if (snake1.getDirection() != Direction::south)
					{
						dirChange = Direction::north;
						dirChanged = true;
					}

					break;
				case Keyboard::D:
					if (snake1.getDirection() != Direction::west)
					{
						dirChange = Direction::east;
						dirChanged = true;
					}

					break;
				case Keyboard::S:
					if (snake1.getDirection() != Direction::north)
					{
						dirChange = Direction::south;
						dirChanged = true;
					}

					break;
				case Keyboard::A:
					if (snake1.getDirection() != Direction::east)
					{
						dirChange = Direction::west;
						dirChanged = true;
					}

					break;
				case Keyboard::Up:
					if (snake2.getDirection() != Direction::south)
					{
						dirChange2 = Direction::north;
						dirChanged2 = true;
					}

					break;
				case Keyboard::Right:
					if (snake2.getDirection() != Direction::west)
					{
						dirChange2 = Direction::east;
						dirChanged2 = true;
					}

					break;
				case Keyboard::Down:
					if (snake2.getDirection() != Direction::north)
					{
						dirChange2 = Direction::south;
						dirChanged2 = true;
					}

					break;
				case Keyboard::Left:
					if (snake2.getDirection() != Direction::east)
					{
						dirChange2 = Direction::west;
						dirChanged2 = true;
					}

					break;
				case Keyboard::Space:
					if (snake1.hasMissle())
					{
						snake1.setMissle(false);
						leftMissle.setPosition(snake1.getPosition(), snake1.getDirection());
						shootMissle(window, board, leftMissle, snake1, snake2, lost2);
					}

					break;
				case Keyboard::RControl:
					if (snake2.hasMissle())
					{
						snake2.setMissle(false);
						rightMissle.setPosition(snake2.getPosition(), snake2.getDirection());
						shootMissle(window, board, rightMissle, snake2, snake1, lost);
					}

					break;
				}
			}
		}
		window.clear();

		if (!loadingDone)
		{
			initialize(board, snake1, snake2, food1, food2, leftMissle, rightMissle, loadingDone);
			clock.restart();
			continue;
		}
		this->segmentCount1.setString(to_string(snake1.getSegmentList().size()));
		this->segmentCount2.setString(to_string(snake2.getSegmentList().size()));

		drawBoard(window, board, snake1, snake2, food1, food2, leftMissle, rightMissle, buffs1, buffs2);

		if (animationClock.getElapsedTime().asMilliseconds() >= 100)
		{
			if (algaeAnimCounter > 0)
			{
				animateBoard(board);
				algaeAnimCounter = 0;
			}
			else
				algaeAnimCounter++;

			animatePickUps(food1, food2, buffs1, buffs2);
			animationClock.restart();
		}

		if (clock.getElapsedTime().asSeconds() >= (0.4 - this->speedUpMod))
		{
			if (lost || lost2)
			{
				if (lost)
				{
					window.draw(loseScreen);
					window.draw(loseText);
				}

				if (lost2)
				{
					loseScreen.setPosition(1152, 384);
					loseText.setPosition(loseScreen.getOrigin().x + 768, loseScreen.getOrigin().y);

					window.draw(loseScreen);
					window.draw(loseText);
				}
				for (cb::Button b : this->buttonSet)
				{
					b.draw(window);
				}

				window.display();

				return endLoop(window, event);
			}

			if (dirChanged)
			{
				dirChanged = false;
				snake1.setDirection(dirChange);
			}
			if (dirChanged2)
			{
				dirChanged2 = false;
				snake2.setDirection(dirChange2);
			}

			if (!snake1.isStunned())
				move(snake1, growth);
			if (!snake2.isStunned())
				move(snake2, growth2, true);

			clock.restart();
		}

		if (snake1.getSegmentList().size() == 20 || snake2.getSegmentList().size() == 20)
		{
			if (snake2.getSegmentList().size() == 20)
			{
				winScreen.setPosition(1152, 384);
				winText.setPosition(winScreen.getOrigin().x + 768, winScreen.getOrigin().y);
			}
			window.draw(winScreen);
			window.draw(winText);

			for (cb::Button b : this->buttonSet)
			{
				b.draw(window);
			}
			window.display();

			return endLoop(window, event);
		}

		if (buffClock.getElapsedTime().asSeconds() > 5)
		{
			buffs1.push_back(Buff(randomizeBuff(), randomizePosition()));
			buffs2.push_back(Buff(randomizeBuff(), randomizePosition(true)));
			buffClock.restart();
		}

		updateCords(board, snake1, snake2, food1, food2, buffs1, buffs2);

		if (swapped)
		{
			if (!lost && !lost2)
			{
				lost = checkCollision(board, snake1, food2, growth, true);
				lost2 = checkCollision(board, snake2, food1, growth2);
			}

			checkBuffStatus(board, snake2, snake1, buffs1);
			checkBuffStatus(board, snake2, snake1, buffs2, true);
		}
		else
		{
			if (!lost && !lost2)
			{
				lost = checkCollision(board, snake1, food1, growth);
				lost2 = checkCollision(board, snake2, food2, growth2, true);
			}

			checkBuffStatus(board, snake1, snake2, buffs1);
			checkBuffStatus(board, snake1, snake2, buffs2, true);
		}

		window.display();
	}
}

void PvP::drawBoard(RenderWindow& window, Board& board, Snake& snake1, Snake& snake2, Food& food1, Food& food2, Missle& leftMissle, Missle& rightMissle, std::vector<Buff> buffs1, std::vector<Buff> buffs2)
{
	board.draw(window);
	snake1.draw(window);
	snake2.draw(window);
	food1.draw(window);
	food2.draw(window);

	window.draw(segmentCount1);
	window.draw(segmentCount2);

	window.draw(leftMissle.getSprite());
	window.draw(rightMissle.getSprite());

	if (snake1.hasMissle())
		window.draw(leftMissleIndicator);
	if (snake2.hasMissle())
		window.draw(rightMissleIndicator);

	for (Buff b : buffs1)
	{
		b.draw(window);
	}
	for (Buff b : buffs2)
	{
		b.draw(window);
	}
}

void PvP::initialize(Board& board, Snake& snake, Snake& snake2, Food& food, Food& food2, Missle& missle1, Missle& missle2, bool& loadingDone)
{
	board.initialize(snake, snake2, food, food2, missle1, missle2, loadingDone);
}

bool PvP::checkCollision(Board& board, Snake& snake, Food& food, bool& growth, bool second)
{

	if (!snake.isElusive() && snake.isCollided())
		return true;

	for (int i = 0; i < board.getWall().size(); i++)
	{
		if (snake.getPosition() == board.getWall().at(i).getSprite().getPosition())
		{
			if (i < 120)
				return true;
			else if (i >= 120 && !snake.isElusive())
				return true;
		}
	}

	if (snake.getPosition() == food.getPosition())
	{
		growth = true;
		Vector2f newPos = randomizePosition(second);
		food.getSprite().setPosition(newPos);
		food.setPosition(newPos);
	}

	return false;
}

void PvP::checkBuffStatus(Board& board, Snake& snake1, Snake& snake2, std::vector<Buff>& buffs, bool second)
{
	for (int i = 0; i < buffs.size(); i++)
	{
		Buff b = buffs.at(i);

		if (!second && snake1.getPosition() == b.getPosition())
		{
			switch (b.getBuffName())
			{
			case BuffName::obstacle:
			{
				buffs.erase(buffs.begin() + i);

				Vector2f cords = randomizePosition(true);
				board.getWall().push_back(Block(ResourceHolder::loadTexture("nautilus"), cords.x, cords.y));
				cords = randomizePosition(true);
				board.getWall().push_back(Block(ResourceHolder::loadTexture("nautilus"), cords.x, cords.y));
				break;
			}
			case BuffName::cut:
			{
				buffs.erase(buffs.begin() + i);

				for (int i = 0; i < 2; i++)
				{
					if (snake2.getSegmentList().size() > 1)
						snake2.getSegmentList().pop_back();
				}
				break;
			}
			case BuffName::noCollision:
			{
				buffs.erase(buffs.begin() + i);

				snake1.setElusiveness();
				break;
			}
			case BuffName::swap:
			{
				buffs.erase(buffs.begin() + i);

				Direction savedDir = snake1.getDirection();
				snake1.setDirection(snake2.getDirection());
				snake2.setDirection(savedDir);


				Vector2f savedPos = snake1.getPosition();
				snake1.setPosition(snake2.getPosition().x, snake2.getPosition().y);
				snake2.setPosition(savedPos.x, savedPos.y);
				
				if (this->swapped)
				{
					snake1.afterSwap(true);
					snake2.afterSwap();
				}
				else
				{
					snake1.afterSwap();
					snake2.afterSwap(true);
				}

				this->swapped = !this->swapped;
				break;
			}
			case BuffName::stun:
			{
				buffs.erase(buffs.begin() + i);

				snake2.setStunned();
				break;
			}
			case BuffName::speedUp:
			{
				buffs.erase(buffs.begin() + i);
				this->speedUpMod = 0.15;

				std::thread speedUpCountdown([this]() {
					Clock speedUpTimer;
					while (1)
					{
						if (speedUpTimer.getElapsedTime().asSeconds() >= 3)
						{
							this->speedUpMod = 0;
							break;
						}
					}
					});
				speedUpCountdown.detach();
				break;
			}
			case BuffName::missle:
			{
				buffs.erase(buffs.begin() + i);

				if(!snake1.hasMissle())
					snake1.setMissle(true);
				break;
			}
			}
		}

		if (second && snake2.getPosition() == b.getPosition())
		{
			switch (b.getBuffName())
			{
			case BuffName::obstacle:
			{
				buffs.erase(buffs.begin() + i);

				Vector2f cords = randomizePosition();
				board.getWall().push_back(Block(ResourceHolder::loadTexture("nautilus"), cords.x, cords.y));
				cords = randomizePosition();
				board.getWall().push_back(Block(ResourceHolder::loadTexture("nautilus"), cords.x, cords.y));
				break;
			}
			case BuffName::cut:
			{
				buffs.erase(buffs.begin() + i);

				for (int i = 0; i < 2; i++)
				{
					if (snake1.getSegmentList().size() > 1)
						snake1.getSegmentList().pop_back();
				}
				break;
			}
			case BuffName::noCollision:
			{
				buffs.erase(buffs.begin() + i);

				snake2.setElusiveness();
				break;
			}

			case BuffName::swap:
			{
				buffs.erase(buffs.begin() + i);

				Direction savedDir = snake1.getDirection();
				snake1.setDirection(snake2.getDirection());
				snake2.setDirection(savedDir);

				Vector2f savedPos = snake1.getPosition();
				snake1.setPosition(snake2.getPosition().x, snake2.getPosition().y);
				snake2.setPosition(savedPos.x, savedPos.y);
				
				if (this->swapped)
				{
					snake1.afterSwap(true);
					snake2.afterSwap();
				}
				else
				{
					snake1.afterSwap();
					snake2.afterSwap(true);
				}
				
				this->swapped = !this->swapped;
				break;
			}
			case BuffName::stun:
			{
				buffs.erase(buffs.begin() + i);

				snake1.setStunned();
				break;
			}
			case BuffName::speedUp:
			{
				buffs.erase(buffs.begin() + i);
				this->speedUpMod = 0.15;

				std::thread speedUpCountdown([this]() {
					Clock speedUpTimer;
					while (1)
					{
						if (speedUpTimer.getElapsedTime().asSeconds() >= 3)
						{
							this->speedUpMod = 0;
							break;
						}
					}
					});
				speedUpCountdown.detach();
				break;
			}

			case BuffName::missle:
			{
				buffs.erase(buffs.begin() + i);

				if(!snake2.hasMissle())
					snake2.setMissle(true);
				break;
			}
			}
		}
	}
}

void PvP::shootMissle(RenderWindow& window, Board& board, Missle& missle, Snake& snake, Snake& other, bool& hit)
{
	switch (snake.getDirection())
	{
	case Direction::north:
		missle.getSprite().setRotation(0);
		break;
	case Direction::east:
		missle.getSprite().setRotation(90);
		break;
	case Direction::south:
		missle.getSprite().setRotation(180);
		break;
	case Direction::west:
		missle.getSprite().setRotation(270);
		break;
	}

	std::thread shoot([&]() {
		Clock missleClock;

		while (1)
		{

			if (missleClock.getElapsedTime().asSeconds() >= 0.125)
			{
				missle.move();
				missleClock.restart();
			}

			for (int i = 120; i < board.getWall().size(); i++)
			{
				if (board.getWall().at(i).getSprite().getPosition() == missle.getSprite().getPosition())
				{
					board.getWall().erase(board.getWall().begin() + i);
				}
			}
			if (other.getPosition() == missle.getSprite().getPosition())
			{
				hit = true;
			}

			if (missle.getSprite().getPosition().x > 1536 || missle.getSprite().getPosition().x < 0 || missle.getSprite().getPosition().y > 768 || missle.getSprite().getPosition().y < 0)
			{
				break;
			}
		};
		});
	shoot.detach();
}

void PvP::move(Snake& snake, bool& growth, bool second)
{
	snake.move(growth, second);
}

BuffName PvP::randomizeBuff()
{

	int x = rand() % 15;

	switch (x)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return BuffName::obstacle;
	case 4:
	case 5:
		return BuffName::cut;
	case 6:
	case 7:
	case 8:
		return BuffName::noCollision;
	case 9:
	case 10:
		return BuffName::stun;
	case 11:
		return BuffName::swap;
	case 12:
	case 13:
		return BuffName::speedUp;
	case 14:
		return BuffName::missle;
	}
}

sf::Vector2f PvP::randomizePosition(bool second)
{

	Vector2f newCords(0,0);

	do
	{
		newCords.x = rand() % 14 + 1;
		if (second)
			newCords.x = newCords.x * 48 + 768;
		else
			newCords.x = newCords.x * 48;


		newCords.y = rand() % 14 + 1;
		newCords.y = newCords.y * 48;

		newCords.x += 24;
		newCords.y += 24;

	} while (checkCollision(newCords));

	return newCords;
}

void PvP::updateCords(Board board, Snake snake1, Snake snake2, Food food1, Food food2, std::vector<Buff> buffs1, std::vector<Buff> buffs2)
{
	this->takenCords.clear();

	for (int i = 120; i < board.getWall().size(); i++)
	{
		this->takenCords.push_back(board.getWall().at(i).getSprite().getPosition());
	}

	for (Buff b : buffs1)
	{
		this->takenCords.push_back(b.getPosition());
	}
	for (Buff b : buffs2)
	{
		this->takenCords.push_back(b.getPosition());
	}
	this->takenCords.push_back(snake1.getPosition());
	this->takenCords.push_back(snake2.getPosition());
	this->takenCords.push_back(food1.getPosition());
	this->takenCords.push_back(food2.getPosition());
}

bool PvP::checkCollision(Vector2f cords)
{
	for (Vector2f v : this->takenCords)
	{
		if (cords.x == v.x)
		{
			if (cords.y == v.y)
				return true;
		}
	}

	return false;
}

bool PvP::endLoop(RenderWindow& window, Event& event)
{
	music.stop();
	while (1)
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				exit(0);
			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (this->buttonSet.at(0).isMouseOver(window))
				{
					window.close();
					return true;
				}
				else if (this->buttonSet.at(1).isMouseOver(window))
				{
					window.close();
					return false;
				}
				else if (this->buttonSet.at(2).isMouseOver(window))
				{
					window.close();
					exit(0);
				}
			}
		}
	}
}

void PvP::resetEndCords()
{
	this->loseScreen.setPosition(Vector2f(384, 384));
	this->winScreen.setPosition(Vector2f(384, 384));
	this->loseText.setPosition(loseScreen.getOrigin());
	this->winText.setPosition(winScreen.getOrigin());
}

void PvP::animatePickUps(Food& food1, Food& food2, std::vector<Buff>& buffs1, std::vector<Buff>& buffs2)
{
	food1.animate();
	food2.animate();

	for (Buff& b : buffs1)
	{
		b.animate();
	}
	for (Buff& b : buffs2)
	{
		b.animate();
	}
}

void PvP::animateBoard(Board& board)
{
	for (int i = 0; i < 120; i++)
	{
		board.getWall()[i].updateAnimation();
	}
}
