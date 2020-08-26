#include "PvP.h"

using namespace sf;
using namespace std;

PvP::PvP()
{
	srand(time(NULL));

	RectangleShape loseScreen(Vector2f(512, 512));
	loseScreen.setFillColor(Color(196, 4, 4, 120));
	loseScreen.setPosition(256, 256);
	loseScreen.setOrigin(loseScreen.getLocalBounds().width / 2, loseScreen.getLocalBounds().height / 2);
	Text loseText;
	loseText.setFont(ResourceHolder::loadFont("lumberjack"));
	loseText.setString("You Lost!");
	loseText.setCharacterSize(50);
	loseText.setOrigin(loseText.getLocalBounds().width / 2, loseText.getLocalBounds().height / 2 + 100);
	loseText.setPosition(loseScreen.getOrigin());
	loseText.setFillColor(Color::Black);

	RectangleShape winScreen(Vector2f(512, 512));
	winScreen.setFillColor(Color(51, 202, 4, 120));
	winScreen.setPosition(256, 256);
	winScreen.setOrigin(winScreen.getLocalBounds().width / 2, winScreen.getLocalBounds().height / 2);
	Text winText;
	winText.setFont(ResourceHolder::loadFont("lumberjack"));
	winText.setString("You Won!");
	winText.setCharacterSize(50);
	winText.setOrigin(winText.getLocalBounds().width / 2, winText.getLocalBounds().height / 2 + 100);
	winText.setPosition(winScreen.getOrigin());
	winText.setFillColor(Color::Black);

	RectangleShape blackScreen(Vector2f(512, 512));
	blackScreen.setFillColor(Color::Black);
	blackScreen.setPosition(0, 0);

	RenderWindow window(VideoMode(1024, 512), "MySnake", Style::Titlebar | Style::Close);

	Image icon;
	for (int i = 0; i < 5; i++)
	{
		icon.loadFromFile("resources/images/snake-icon.png");
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Board board;
	Event event;
	Clock clock;
	Clock buffClock;

	bool loadingDone = false;
	bool threading = true;


	Snake snake1(128, 128);
	Food food1;
	Direction dirChange;
	bool dirChanged = false;
	bool growth = false;
	bool lost = false;
	std::vector<Buff> buffs1;

	Snake snake2(896, 128);
	Food food2(true);
	Direction dirChange2;
	bool dirChanged2 = false;
	bool growth2 = false;
	bool lost2 = false;
	std::vector<Buff> buffs2;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;

			case Event::KeyPressed: //In case of any problems change to if((event.key.code == K::) && event.key.code != snake.prevDir) ([prevDir = dir] in move())
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
				}
			}
		}
		window.clear();

		if (!loadingDone)
		{
			if (threading)
			{
				std::thread loading(&PvP::initialize, this, std::ref(board), std::ref(snake1), std::ref(snake2), std::ref(food1), std::ref(food2), std::ref(loadingDone));
				loading.detach();
				threading = false;
			}

			window.draw(blackScreen);
			window.display();
			clock.restart();
			continue;
		}

		board.draw(window);
		snake1.draw(window);
		snake2.draw(window);
		food1.draw(window);
		food2.draw(window);

		for (Buff b : buffs1)
		{
			b.draw(window);
		}
		for (Buff b : buffs2)
		{
			b.draw(window);
		}

		if (clock.getElapsedTime().asSeconds() >= 0.5)
		{
			if (snake1.isElusive())
				cout << "Wegorz1 jest elusywny" << endl;
			if (snake2.isElusive())
				cout << "Wegorz1 jest elusywny" << endl;

			//std::thread moveSnake(&SinglePlayer::move, this, std::ref(snake));
			//moveSnake.detach();
			if (lost || lost2)
			{
				if (lost)
				{
					window.draw(loseScreen);
					window.draw(loseText);
				}

				if (lost2)
				{
					loseScreen.setPosition(768, 256);
					loseText.setPosition(loseScreen.getOrigin().x + 512, loseScreen.getOrigin().y);

					window.draw(loseScreen);
					window.draw(loseText);
				}
				window.display();

				while (1)
				{
					while (window.pollEvent(event))
					{
						if (event.type == Event::Closed)
						{
							window.close();
							break;
						}
					}
				}
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
			move(snake1, growth);
			move(snake2, growth2);
			clock.restart();
		}

		if (snake1.getSegmentList().size() == 20 || snake2.getSegmentList().size() == 20)
		{
			if (snake2.getSegmentList().size() == 20)
			{
				winScreen.setPosition(768, 256);
				winText.setPosition(winScreen.getOrigin().x + 512, winScreen.getOrigin().y);
			}
			window.draw(winScreen);
			window.draw(winText);
			window.display();

			while (1)
			{
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
					{
						window.close();
						break;
					}
				}
			}
		}

		if (buffClock.getElapsedTime().asSeconds() > 5)
		{
			buffs1.push_back(Buff(randomizeBuff(), randomizePosition()));
			buffs2.push_back(Buff(randomizeBuff(), randomizePosition(true)));
			buffClock.restart();
		}

		updateCords(board, snake1, snake2, food1, food2, buffs1, buffs2);

		lost = checkCollision(board, snake1, food1, growth);
		lost2 = checkCollision(board, snake2, food2, growth2, true);

		checkBuffStatus(board, snake1, snake2, buffs1);
		checkBuffStatus(board, snake1, snake2, buffs2, true);

		window.display();
	}
}

void PvP::initialize(Board& board, Snake& snake, Snake& snake2, Food& food, Food& food2, bool& loadingDone)
{
	board.initialize(snake, snake2, food, food2, loadingDone);
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

	//for (Block b : board.getWall())
	//{
	//	if (snake.getPosition() == b.getSprite().getPosition())
	//	{
	//		
	//		return true;
	//	}
	//}

	if (snake.getPosition() == food.getPosition())
	{
		cout << "oj tak snejq +1" << endl;
		growth = true;

		Vector2f newPos = randomizePosition(second);
		food.getSprite().setPosition(newPos);
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

				board.getWall().push_back(Block(ResourceHolder::loadTexture("nautilus"), cords.x, cords.y));;
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
				snake1.afterSwap();
				snake2.setPosition(savedPos.x, savedPos.y);
				snake2.afterSwap();
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

				board.getWall().push_back(Block(ResourceHolder::loadTexture("nautilus"), cords.x, cords.y));;
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
				snake1.afterSwap();
				snake2.setPosition(savedPos.x, savedPos.y);
				snake2.afterSwap();
				break;
			}
			}
		}
	}
}

void PvP::move(Snake& snake, bool& growth)
{
	snake.move(growth);
}

BuffName PvP::randomizeBuff()
{

	int x = rand() % 4;

	switch (x)
	{
	case 0:
		return BuffName::obstacle;
	case 1:
		return BuffName::cut;
	case 2:
		return BuffName::noCollision;
	case 3:
		return BuffName::swap;
	}
}

sf::Vector2f PvP::randomizePosition(bool second)
{

	Vector2f newCords(0,0);

	do
	{
		newCords.x = rand() % 14 + 1;
		if (second)
			newCords.x = newCords.x * 32 + 512;
		else
			newCords.x = newCords.x * 32;


		newCords.y = rand() % 14 + 1;
		newCords.y = newCords.y * 32;

		newCords.x += 16;
		newCords.y += 16;

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

	//for (Block b : board.getWall())
	//{
	//	this->takenCords.push_back(b.getSprite().getPosition());
	//}
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
