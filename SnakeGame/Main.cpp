#include "Button.h"
#include "SinglePlayer.h"
#include <iostream>

using namespace sf;
using namespace std;


int main()
{
	Font font;
	for (int i = 0; i < 5; i++)
	{
		font.loadFromFile("resources/fonts/Lumberjack.otf");
	}
	Image icon;
	for (int i = 0; i < 5; i++)
	{
		icon.loadFromFile("resources/images/snake-icon.png");
	}

	RenderWindow window(VideoMode(400, 600), "MySnake", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	Event event;

	cb::Button singleButton(Vector2f(105, 80), Vector2f(190, 90), Color(10, 150, 50), 8, Color(80, 150, 120), "PLAY", Vector2f(145, 85), 55);
	singleButton.setFont(font);

	cb::Button pvpButton(Vector2f(105, 250), Vector2f(190, 90), Color(63, 165, 209), 8, Color(80, 100, 180), "PvP", Vector2f(158, 255), 55);
	pvpButton.setFont(font);

	cb::Button exitButton(Vector2f(105, 420), Vector2f(190, 90), Color(150, 10, 50), 8, Color(150, 80, 120), "EXIT", Vector2f(150, 425), 55);
	exitButton.setFont(font);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;

			case Event::MouseButtonPressed:
				if (singleButton.isMouseOver(window))
				{
					SinglePlayer();
				}
			}
		}
		window.clear();

		singleButton.draw(window);
		pvpButton.draw(window);
		exitButton.draw(window);

		window.display();
	}

	return 0;
}