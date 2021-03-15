#include "ModifierInfo.h"

ModifierInfo::ModifierInfo() 
	: startButton(Vector2f(880, 667), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "START", Vector2f(910, 677), 45)
{
	for (int i = 0; i < 5; i++)
	{
		this->icon.loadFromFile("../resources/images/snake-icon.png");
	}
	this->background.setTexture(ResourceHolder::loadTexture("background-info"));
	this->background.setPosition(0, 0);
	this->startButton.setFont(ResourceHolder::loadFont("roboto-thin"));
}

void ModifierInfo::showInfo()
{
	RenderWindow window(VideoMode(1170, 787), "The Eel", Style::Titlebar | Style::Close);
	window.setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
	Event event;

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
				if (this->startButton.isMouseOver(window))
				{
					window.close();
					while (pvp.play()) {}
				}
			}
		}
		window.clear();

		draw(window);

		window.display();
	}
}

void ModifierInfo::draw(RenderWindow& window)
{
	window.draw(this->background);
	this->startButton.draw(window);
}
