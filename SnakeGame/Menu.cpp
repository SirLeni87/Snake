#include "Menu.h"

using namespace sf;
using namespace std;

void Menu::menu(bool single)
{
	Image icon;
	for (int i = 0; i < 5; i++)
	{
		icon.loadFromFile("resources/images/snake-icon.png");
	}

	RenderWindow window(VideoMode(1170, 787), "The Eel", Style::Titlebar | Style::Close);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	Event event;

	Sprite menuBackground;
	menuBackground.setTexture(ResourceHolder::loadTexture("menu"));
	menuBackground.setPosition(0, 0);

		cb::Button chilloutButton(Vector2f(495, 235), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "CHILLOUT", Vector2f(495, 248), 41);
		chilloutButton.setFont(ResourceHolder::loadFont("roboto-thin"));

		cb::Button easyButton(Vector2f(495, 365), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "EASY", Vector2f(527, 370), 55);
		easyButton.setFont(ResourceHolder::loadFont("roboto-thin"));

		cb::Button normalButton(Vector2f(495, 495), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "NORMAL", Vector2f(497, 505), 47);
		normalButton.setFont(ResourceHolder::loadFont("roboto-thin"));

		cb::Button hardButton(Vector2f(495, 625), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "HARD", Vector2f(519, 630), 55);
		hardButton.setFont(ResourceHolder::loadFont("roboto-thin"));

		cb::Button singleButton(Vector2f(495, 250), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "PLAY", Vector2f(526, 255), 55);
		singleButton.setFont(ResourceHolder::loadFont("roboto-thin"));

		cb::Button pvpButton(Vector2f(495, 400), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "PvP", Vector2f(543, 405), 55);
		pvpButton.setFont(ResourceHolder::loadFont("roboto-thin"));

		cb::Button exitButton(Vector2f(495, 550), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "EXIT", Vector2f(534, 555), 55);
		exitButton.setFont(ResourceHolder::loadFont("roboto-thin"));

		chilloutButton.setActive(false);
		easyButton.setActive(false);
		normalButton.setActive(false);
		hardButton.setActive(false);


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
					chilloutButton.setActive(true);
					easyButton.setActive(true);
					normalButton.setActive(true);
					hardButton.setActive(true);

					singleButton.setActive(false);
					pvpButton.setActive(false);
					exitButton.setActive(false);
				}
				else if (pvpButton.isMouseOver(window))
				{
					window.close();
					PvP::PvP();
				}
				else if (exitButton.isMouseOver(window))
				{
					window.close();
					exit(0);
				}
				else if (chilloutButton.isMouseOver(window))
				{
					window.close();
					SinglePlayer::SinglePlayer(0);
				}
				else if (easyButton.isMouseOver(window))
				{
					window.close();
					SinglePlayer::SinglePlayer(0.001);
				}
				else if (normalButton.isMouseOver(window))
				{
					window.close();
					SinglePlayer::SinglePlayer(0.0015);
				}
				else if (hardButton.isMouseOver(window))
				{
					window.close();
					SinglePlayer::SinglePlayer(0.002);
				}
			}
		}
		window.clear();

		window.draw(menuBackground);

		singleButton.draw(window);
		pvpButton.draw(window);
		exitButton.draw(window);

		chilloutButton.draw(window);
		easyButton.draw(window);
		normalButton.draw(window);
		hardButton.draw(window);

		window.display();
	}

	return;
}