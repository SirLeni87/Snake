#include "SinglePlayer.h"

using namespace sf;
using namespace std;

SinglePlayer::SinglePlayer()
{
	RectangleShape loseScreen(Vector2f(512, 512));
	loseScreen.setFillColor(Color(196, 4, 4, 120));
	loseScreen.setPosition(256, 256);
	loseScreen.setOrigin(loseScreen.getLocalBounds().width /2, loseScreen.getLocalBounds().height / 2);
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
	winScreen.setOrigin(winScreen.getLocalBounds().width /2, winScreen.getLocalBounds().height / 2);
	Text winText;
	winText.setFont(ResourceHolder::loadFont("lumberjack"));
	winText.setString("You Won!");
	winText.setCharacterSize(50);
	winText.setOrigin(winText.getLocalBounds().width / 2, winText.getLocalBounds().height / 2 + 100);
	winText.setPosition(winScreen.getOrigin());
	winText.setFillColor(Color::Black);
		
	RectangleShape blackScreen(Vector2f(512,512));
	blackScreen.setFillColor(Color::Black);
	blackScreen.setPosition(0,0);

	RenderWindow window(VideoMode(512, 512), "MySnake", Style::Titlebar | Style::Close);

	Image icon;
	for (int i = 0; i < 5; i++)
	{
		icon.loadFromFile("resources/images/snake-icon.png");
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Board board;
	Event event;
	Snake snake(128, 128);
	Food food;
	Clock clock;

	bool loadingDone = false;
	bool threading = true;
	bool growth = false;
	bool dirChanged = false;

	Direction dirChange;

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
					if (snake.getDirection() != Direction::south)
						//snake.setDirection(Direction::north);
					{
						dirChange = Direction::north;
						dirChanged = true;
					}

					break;
				case Keyboard::D:
					if (snake.getDirection() != Direction::west)
						//snake.setDirection(Direction::east);
					{
						dirChange = Direction::east;
						dirChanged = true;
					}

					break;
				case Keyboard::S:
					if (snake.getDirection() != Direction::north)
						//snake.setDirection(Direction::south);
					{
						dirChange = Direction::south;
						dirChanged = true;
					}

					break;
				case Keyboard::A:
					if (snake.getDirection() != Direction::east)
						//snake.setDirection(Direction::west);
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

			window.draw(blackScreen);
			window.display();
			clock.restart();
			continue;
		}

		if (clock.getElapsedTime().asSeconds() >= 0.5)
		{
			//std::thread moveSnake(&SinglePlayer::move, this, std::ref(snake));
			//moveSnake.detach();
			if (dirChanged)
			{
				dirChanged = false;
				snake.setDirection(dirChange);
			}
			move(snake, growth);
			clock.restart();
		}

		//if (checkCollision(board, snake, food, growth))
		//{
		//	lost = true;
		//}

		board.draw(window);
		snake.draw(window);
		food.draw(window);

		if (snake.getSegmentList().size() == 20)
		{
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
		if (checkCollision(board, snake, food, growth))
		{
			window.draw(loseScreen);
			window.draw(loseText);
			window.display();

			while (1)
			{
				while(window.pollEvent(event))
				{
					if (event.type == Event::Closed)
					{
						window.close();
						break;
					}
				}
			}
		}

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
		cout << "oj tak snejq +1" << endl;
		growth = true;
		food.newPosition();
	}

	return false;
}

void SinglePlayer::move(Snake& snake, bool& growth)
{
	snake.move(growth);
}