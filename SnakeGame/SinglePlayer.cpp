#include "SinglePlayer.h"

using namespace sf;
using namespace std;

SinglePlayer::SinglePlayer(float difficulty)
{
	RectangleShape loseScreen(Vector2f(768, 768));
	loseScreen.setFillColor(Color(196, 4, 4, 120));
	loseScreen.setPosition(384, 384);
	loseScreen.setOrigin(loseScreen.getLocalBounds().width /2, loseScreen.getLocalBounds().height / 2);
	Text loseText;
	loseText.setFont(ResourceHolder::loadFont("lumberjack"));
	loseText.setString("You Lost!");
	loseText.setCharacterSize(70);
	loseText.setOrigin(loseText.getLocalBounds().width / 2, loseText.getLocalBounds().height / 2 + 100);
	loseText.setPosition(loseScreen.getOrigin());
	loseText.setFillColor(Color::Black);

	RectangleShape winScreen(Vector2f(768, 768));
	winScreen.setFillColor(Color(51, 202, 4, 120));
	winScreen.setPosition(384, 384);
	winScreen.setOrigin(winScreen.getLocalBounds().width /2, winScreen.getLocalBounds().height / 2);
	Text winText;
	winText.setFont(ResourceHolder::loadFont("lumberjack"));
	winText.setString("You Won!");
	winText.setCharacterSize(70);
	winText.setOrigin(winText.getLocalBounds().width / 2, winText.getLocalBounds().height / 2 + 100);
	winText.setPosition(winScreen.getOrigin());
	winText.setFillColor(Color::Black);
		
	RectangleShape blackScreen(Vector2f(768, 768));
	blackScreen.setFillColor(Color::Black);
	blackScreen.setPosition(0,0);

	cb::Button restartButton(Vector2f(30, 550), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "RESTART", Vector2f(32, 560), 45);
	restartButton.setFont(ResourceHolder::loadFont("roboto-thin"));

	cb::Button menuButton(Vector2f(289, 550), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "MENU", Vector2f(309, 555), 55);
	menuButton.setFont(ResourceHolder::loadFont("roboto-thin"));

	cb::Button exitButton(Vector2f(548, 550), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "EXIT", Vector2f(589, 555), 55);
	exitButton.setFont(ResourceHolder::loadFont("roboto-thin"));


	RenderWindow window(VideoMode(768, 768), "The Eel", Style::Titlebar | Style::Close);

	Image icon;
	for (int i = 0; i < 5; i++)
	{
		icon.loadFromFile("resources/images/snake-icon.png");
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Board board;
	Event event;
	Snake snake(192, 192);
	Food food;
	Clock clock;

	Text segmentCount;
	segmentCount.setFont(ResourceHolder::loadFont("roboto-thin"));
	segmentCount.setString(to_string(snake.getSegmentList().size()));
	segmentCount.setCharacterSize(60);
	segmentCount.setPosition(376, 50);
	segmentCount.setFillColor(Color(92, 177, 219));

	bool loadingDone = false;
	bool threading = true;
	bool growth = false;
	bool dirChanged = false;

	Direction dirChange;

	float velocityChange = difficulty; //hard - 0.002, medium - 0.0015, easy - 0.001, chillout - 0
	float speedUp = 0;

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

			window.draw(blackScreen);
			window.display();
			clock.restart();
			continue;
		}

		if (clock.getElapsedTime().asSeconds() >= (0.5 - speedUp))
		{
			if (dirChanged)
			{
				dirChanged = false;
				snake.setDirection(dirChange);
			}
			move(snake, growth);
			clock.restart();
			speedUp += velocityChange;
		}
		segmentCount.setString(to_string(snake.getSegmentList().size()));

		board.draw(window);
		snake.draw(window);
		food.draw(window);
		window.draw(segmentCount);

		window.display();

		if (snake.getSegmentList().size() == 20)
		{
			window.draw(winScreen);
			window.draw(winText);

			restartButton.draw(window);
			menuButton.draw(window);
			exitButton.draw(window);

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
					if (event.type == Event::MouseButtonPressed)
					{
						if (restartButton.isMouseOver(window))
						{
							window.close();
							SinglePlayer::SinglePlayer(difficulty);
						}
						else if (menuButton.isMouseOver(window))
						{
							window.close();
							Menu::menu();
						}
						else if (exitButton.isMouseOver(window))
						{
							window.close();
							exit(0);
						}
					}
				}
			}
		}
		if (checkCollision(board, snake, food, growth))
		{
			window.draw(loseScreen);
			window.draw(loseText);

			restartButton.draw(window);
			menuButton.draw(window);
			exitButton.draw(window);

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
					if (event.type == Event::MouseButtonPressed)
					{
						if (restartButton.isMouseOver(window))
						{
							window.close();
							SinglePlayer::SinglePlayer(difficulty);
						}
						else if (menuButton.isMouseOver(window))
						{
							window.close();
							Menu::menu();
						}
						else if (exitButton.isMouseOver(window))
						{
							window.close();
							exit(0);
						}
					}
				}
			}
		}
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