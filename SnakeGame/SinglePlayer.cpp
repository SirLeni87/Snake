#include "SinglePlayer.h"


SinglePlayer::SinglePlayer() : loseScreen(Vector2f(768, 768)), winScreen(Vector2f(768, 768))
{
	for (int i = 0; i < 5; i++)
	{
		this->icon.loadFromFile("../resources/images/icon.png");
	}

	this->loseScreen.setFillColor(Color(196, 4, 4, 120));
	this->loseScreen.setPosition(384, 384);
	this->loseScreen.setOrigin(loseScreen.getLocalBounds().width / 2, loseScreen.getLocalBounds().height / 2);
	this->loseText.setFont(ResourceHolder::loadFont("lumberjack"));
	this->loseText.setString("You Lost!");
	this->loseText.setCharacterSize(70);
	this->loseText.setOrigin(loseText.getLocalBounds().width / 2, loseText.getLocalBounds().height / 2 + 100);
	this->loseText.setPosition(loseScreen.getOrigin());
	this->loseText.setFillColor(Color::Black);

	this->winScreen.setFillColor(Color(51, 202, 4, 120));
	this->winScreen.setPosition(384, 384);
	this->winScreen.setOrigin(winScreen.getLocalBounds().width / 2, winScreen.getLocalBounds().height / 2);
	this->winText.setFont(ResourceHolder::loadFont("lumberjack"));
	this->winText.setString("You Won!");
	this->winText.setCharacterSize(70);
	this->winText.setOrigin(winText.getLocalBounds().width / 2, winText.getLocalBounds().height / 2 + 100);
	this->winText.setPosition(winScreen.getOrigin());
	this->winText.setFillColor(Color::Black);

	this->buttonSet.push_back(cb::Button(Vector2f(30, 550), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "RESTART", Vector2f(32, 560), 45));
	this->buttonSet.push_back(cb::Button(Vector2f(289, 550), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "MENU", Vector2f(309, 555), 55));
	this->buttonSet.push_back(cb::Button(Vector2f(548, 550), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "EXIT", Vector2f(589, 555), 55));

	for (cb::Button& b : this->buttonSet)
	{
		b.setFont(ResourceHolder::loadFont("roboto-thin"));
	}

	this->segmentCount.setFont(ResourceHolder::loadFont("roboto-thin"));
	this->segmentCount.setCharacterSize(60);
	this->segmentCount.setPosition(376, 50);
	this->segmentCount.setFillColor(Color(92, 177, 219));
}

bool SinglePlayer::play(float difficulty)
{
	RenderWindow window(VideoMode(768, 768), "The Eel", Style::Titlebar | Style::Close);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Snake snake(192, 192);
	Board board;
	Event event;
	Food food;

	Clock clock;
	Clock animationClock;

	this->segmentCount.setString(to_string(snake.getSegmentList().size()));

	bool loadingDone = false;
	bool threading = true;
	bool growth = false;
	bool dirChanged = false;
	bool lost = false;

	Direction dirChange;

	float velocityChange = difficulty; //hard - 0.002, medium - 0.0015, easy - 0.001, chillout - 0
	float speedUp = 0;

	int algaeAnimCounter = 0;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				exit(0);

			case Event::KeyPressed: //In case of any problems change to if((event.key.code == K::) && event.key.code != snake.prevDir) ([prevDir = dir] in move())
				switch (event.key.code)
				{
				case Keyboard::W:
					if (snake.getDirection() != Direction::south)
					{
						dirChange = Direction::north;
						dirChanged = true;
					}

					break;
				case Keyboard::D:
					if (snake.getDirection() != Direction::west)
					{
						dirChange = Direction::east;
						dirChanged = true;
					}

					break;
				case Keyboard::S:
					if (snake.getDirection() != Direction::north)
					{
						dirChange = Direction::south;
						dirChanged = true;
					}

					break;
				case Keyboard::A:
					if (snake.getDirection() != Direction::east)
					{
						dirChange = Direction::west;
						dirChanged = true;
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
				std::thread loading(&SinglePlayer::initialize, this, std::ref(board), std::ref(snake), std::ref(food), std::ref(loadingDone));
				loading.detach();
				threading = false;
			}
			clock.restart();
			continue;
		}
		this->segmentCount.setString(to_string(snake.getSegmentList().size()));

		board.draw(window);
		snake.draw(window);
		food.draw(window);
		window.draw(this->segmentCount);

		if (animationClock.getElapsedTime().asMilliseconds() >= 100)
		{
			if (algaeAnimCounter > 0)
			{
				animateBoard(board);
				algaeAnimCounter = 0;
			}
			else
				algaeAnimCounter++;

			food.animate();
			animationClock.restart();
		}


		if (clock.getElapsedTime().asSeconds() >= (0.5 - speedUp))
		{
			if (lost)
			{
				return endGame(window, event, false);
			}

			if (dirChanged)
			{
				dirChanged = false;
				snake.setDirection(dirChange);
			}
			move(snake, growth);
			clock.restart();
			speedUp += velocityChange;
		}

		if (snake.getSegmentList().size() == 20)
		{
			return endGame(window, event, true);
		}

		lost = checkCollision(board, snake, food, growth);

		window.display();
	}
}

void SinglePlayer::initialize(Board& board, Snake& snake, Food& food, bool& loadingDone)
{
	board.initialize(snake, food, loadingDone);
}

bool SinglePlayer::checkCollision(Board& board, Snake& snake, Food& food, bool& growth)
{
	if (snake.isCollided())
		return true;

	for (Block b : board.getWall())
	{
		if (snake.getPosition() == b.getSprite().getPosition())
		{
			return true;
		}
	}

	if (snake.getPosition() == food.getPosition())
	{
		growth = true;
		food.newPosition();
	}

	return false;
}

void SinglePlayer::move(Snake& snake, bool& growth)
{
	snake.move(growth);
}

bool SinglePlayer::endGame(RenderWindow& window, Event& event, bool win)
{
	if (win)
	{
		window.draw(this->winScreen);
		window.draw(this->winText);
	}
	else
	{
		window.draw(this->loseScreen);
		window.draw(this->loseText);
	}

	for (cb::Button b : this->buttonSet)
	{
		b.draw(window);
	}

	window.display();

	return endLoop(window, event);
}

bool SinglePlayer::endLoop(RenderWindow& window, Event& event)
{
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

void SinglePlayer::animateBoard(Board& board)
{
	for (Block& b : board.getWall())
	{
		b.updateAnimation();
	}
}
