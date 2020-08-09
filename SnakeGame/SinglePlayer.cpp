#include "SinglePlayer.h"

using namespace sf;
using namespace std;

SinglePlayer::SinglePlayer()
{

	RectangleShape blackScreen(Vector2f(512,512));
	blackScreen.setFillColor(Color::Black);
	blackScreen.setPosition(0,0);

	RenderWindow window(VideoMode(512, 512), "MySnake", Style::Titlebar | Style::Close);

	Board board;
	Event event;
	Snake snake(128, 128);
	Food food;
	Clock clock;

	bool loadingDone = false;
	bool threading = true;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;

			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::W:
					if(snake.getDirection() != Direction::south)
						snake.setDirection(Direction::north);

					break;
				case Keyboard::D:
					if (snake.getDirection() != Direction::west)
						snake.setDirection(Direction::east);

					break;
				case Keyboard::S:
					if (snake.getDirection() != Direction::north)
						snake.setDirection(Direction::south);

					break;
				case Keyboard::A:
					if (snake.getDirection() != Direction::east)
						snake.setDirection(Direction::west);

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

		if (clock.getElapsedTime().asSeconds() >= 1)
		{
			std::thread moveSnake(&SinglePlayer::move, this, std::ref(snake));
			moveSnake.detach();
			clock.restart();
		}


		checkCollision(board, snake, food);

		board.draw(window);
		snake.draw(window);
		food.draw(window);
		window.display();
	}
}

void SinglePlayer::initialize(Board& board, Snake& snake, Food& food, bool& loadingDone)
{
	board.initialize(snake, food, loadingDone);
}

void SinglePlayer::checkCollision(Board& board, Snake& snake, Food& food)
{
	for (Block b : board.getWall())
	{
		if (snake.getPosition() == b.getRect().getPosition())
		{
			cout << "oj nie snejq -1" << endl;
			break;
		}
	}

	if (snake.getPosition() == food.getPosition())
	{
		cout << "oj tak snejq +1" << endl;
		food.newPosition();
	}
}

void SinglePlayer::move(Snake& snake)
{
	snake.move();
}
