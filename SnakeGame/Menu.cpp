#include "Menu.h"

Menu::Menu() : window(VideoMode(1170, 787), "The Eel", Style::Titlebar | Style::Close)
{
	Image icon;
	for (int i = 0; i < 5; i++)
	{
		icon.loadFromFile("resources/images/snake-icon.png");
	}

	this->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	this->menuBackground.setTexture(ResourceHolder::loadTexture("menu"));
	this->menuBackground.setPosition(0, 0);

	this->buttonSet1.push_back(cb::Button(Vector2f(495, 250), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "PLAY", Vector2f(526, 255), 55));
	this->buttonSet1.push_back(cb::Button(Vector2f(495, 400), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "PvP", Vector2f(543, 405), 55));
	this->buttonSet1.push_back(cb::Button(Vector2f(495, 550), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "EXIT", Vector2f(534, 555), 55));

	this->buttonSet2.push_back(cb::Button(Vector2f(495, 235), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "CHILLOUT", Vector2f(495, 248), 41));
	this->buttonSet2.push_back(cb::Button(Vector2f(495, 365), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "EASY", Vector2f(527, 370), 55));
	this->buttonSet2.push_back(cb::Button(Vector2f(495, 495), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "NORMAL", Vector2f(497, 505), 47));
	this->buttonSet2.push_back(cb::Button(Vector2f(495, 625), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "HARD", Vector2f(519, 630), 55));

	for (cb::Button& b : this->buttonSet1)
	{
		b.setFont(ResourceHolder::loadFont("roboto-thin"));
	}
	for (cb::Button& b : this->buttonSet2)
	{
		b.setFont(ResourceHolder::loadFont("roboto-thin"));
		b.setActive(!b.getActiveStatus());
	}
}

void Menu::menu()
{
	Event event;
	SinglePlayer singlePlayer;
	ModifierInfo modifierInfo;
	//PvP pvp;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				exit(0);

			case Event::MouseButtonPressed:
				if (this->buttonSet1.at(0).isMouseOver(window))
				{
					switchButtons();
				}
				else if (this->buttonSet1.at(1).isMouseOver(window))
				{
					window.setVisible(false);
					modifierInfo.showInfo();
					window.setVisible(true);
				}
				else if (this->buttonSet1.at(2).isMouseOver(window))
				{
					window.close();
					exit(0);
				}
				else if (this->buttonSet2.at(0).isMouseOver(window))
				{
					window.setVisible(false);
					while (singlePlayer.play(0)) {}
					switchButtons();
					window.setVisible(true);
				}
				else if (this->buttonSet2.at(1).isMouseOver(window))
				{
					window.setVisible(false);
					while (singlePlayer.play(0.001)) {}
					switchButtons();
					window.setVisible(true);
				}
				else if (this->buttonSet2.at(2).isMouseOver(window))
				{
					window.setVisible(false);
					while (singlePlayer.play(0.0015)) {}
					switchButtons();
					window.setVisible(true);
				}
				else if (this->buttonSet2.at(3).isMouseOver(window))
				{
					window.setVisible(false);
					while (singlePlayer.play(0.002)) {}
					switchButtons();
					window.setVisible(true);
				}
			}
		}
		window.clear();

		draw(window);

		window.display();
	}

	return;
}

void Menu::switchButtons()
{
	for (cb::Button& b : this->buttonSet1)
	{
		b.setActive(!b.getActiveStatus());
	}
	for (cb::Button& b : this->buttonSet2)
	{
		b.setActive(!b.getActiveStatus());
	}
}

void Menu::draw(RenderWindow& window)
{
	window.draw(this->menuBackground);
	for (cb::Button& b : this->buttonSet1)
	{
		b.draw(window);
	}
	for (cb::Button& b : this->buttonSet2)
	{
		b.draw(window);
	}
}
