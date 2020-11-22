#include "ModifierInfo.h"

ModifierInfo::ModifierInfo() 
	: startButton(Vector2f(880, 600), Vector2f(190, 90), Color(230, 230, 230), 8, Color(225, 225, 225), "START", Vector2f(910, 610), 45)
{
	for (int i = 0; i < 5; i++)
	{
		this->icon.loadFromFile("resources/images/snake-icon.png");
	}
	this->background.setTexture(ResourceHolder::loadTexture("background-info"));
	this->background.setPosition(0, 0);
	this->startButton.setFont(ResourceHolder::loadFont("roboto-thin"));

	this->sprites.push_back(Sprite(ResourceHolder::loadTexture("fish1")));
	this->sprites.push_back(Sprite(ResourceHolder::loadTexture("fish2")));
	this->sprites.push_back(Sprite(ResourceHolder::loadTexture("pufferfish")));
	this->sprites.push_back(Sprite(ResourceHolder::loadTexture("shrimp")));
	this->sprites.push_back(Sprite(ResourceHolder::loadTexture("jellyfish")));
	this->sprites.push_back(Sprite(ResourceHolder::loadTexture("crab")));
	this->sprites.push_back(Sprite(ResourceHolder::loadTexture("net")));
	this->sprites.push_back(Sprite(ResourceHolder::loadTexture("sailfish")));
	this->sprites.push_back(Sprite(ResourceHolder::loadTexture("whirlpool")));
	this->sprites.push_back(Sprite(ResourceHolder::loadTexture("nautilus")));
	this->sprites.push_back(Sprite(ResourceHolder::loadTexture("shell")));
	this->sprites.push_back(Sprite(ResourceHolder::loadTexture("indicator")));

	this->texts.push_back(Text("Eel's food. Eating it will make the eel frow by one segment.", ResourceHolder::loadFont("roboto-regular"), 18));
	this->texts.push_back(Text("Eating a pufferfish will shrink the opposite eel by 2 segments.", ResourceHolder::loadFont("roboto-regular"), 18));
	this->texts.push_back(Text("Eating a shrimp will cause 2 nautiluses			to appear on the opposite site. Nautiluses work as additinal unpassable block.\n"
		"Be cautious, because they appear randomly on any available tile.", ResourceHolder::loadFont("roboto-regular"), 18));
	this->texts.push_back(Text("Eating a jellyfish gives the eel an ability to pass through its segments and nautiluses. Eel's flickering indicates that there are 2 or\n"
		"less seconds left of this modifier's influence.", ResourceHolder::loadFont("roboto-regular"), 18));
	this->texts.push_back(Text("Eating a hermit crab gives the eel a shell missle		that can be shot by pressing SPACE (left player) or RIGHT CTRL (right player) at\n"
		"the direction the eel is curently facing. The missle will destroy encountered nautiluses and kill the opposite eel, if it hits the eel's head.\n"
		"If the player has a missle available, the indicator		 on the adequate site will appear.", ResourceHolder::loadFont("roboto-regular"), 18));
	this->texts.push_back(Text("Collecting a fishing net will stun the opposite eel for 2 seconds.", ResourceHolder::loadFont("roboto-regular"), 18));
	this->texts.push_back(Text("Eating a sailfish will speed up both eels for 3 seconds.", ResourceHolder::loadFont("roboto-regular"), 18));
	this->texts.push_back(Text("Swimming into a whirlpool causes both eels to swap places and directions they are facing.", ResourceHolder::loadFont("roboto-regular"), 18));
	this->texts.push_back(Text("The game ends when one eel gets to be 20 segments long, or when one \n"
		"of the players (or both, if they hit something at the same time) loses.", ResourceHolder::loadFont("roboto-regular"), 25));

	for (int i = 0; i < this->texts.size() - 1; i++)
	{
		this->texts.at(i).setPosition(60, 192 + i*48);
	}
	this->texts.at(0).setPosition(80, 205);
	this->texts.at(1).setPosition(80, 252);
	this->texts.at(2).setPosition(80, 290);
	this->texts.at(3).setPosition(80, 345);
	this->texts.at(4).setPosition(80, 396);
	this->texts.at(5).setPosition(80, 470);
	this->texts.at(6).setPosition(80, 520);
	this->texts.at(7).setPosition(80, 580);
	this->texts.at(8).setPosition(20, 650);

	this->sprites.at(0).setScale(0.6, 0.6);
	this->sprites.at(1).setScale(0.6, 0.6);
	for (int i = 2; i < this->sprites.size()-3; i++)
	{
		this->sprites.at(i).setScale(0.75, 0.75);
	}
	this->sprites.at(this->sprites.size() - 1).setScale(0.6, 0.6);
	this->sprites.at(this->sprites.size() - 2).setScale(0.6, 0.6);
	this->sprites.at(this->sprites.size() - 3).setScale(0.6, 0.6);

	this->sprites.at(0).setPosition(1, 200);
	this->sprites.at(1).setPosition(38, 200);
	for (int i = 2; i < this->sprites.size() - 3; i++)
	{
		this->sprites.at(i).setPosition(10, 240 + 55*(i-2));
	}
	this->sprites.at(this->sprites.size() - 1).setPosition(465, 433);
	this->sprites.at(this->sprites.size() - 2).setPosition(460, 383);
	this->sprites.at(this->sprites.size() - 3).setPosition(398, 280);
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
	for (Sprite s : this->sprites)
	{
		window.draw(s);
	}
	for (Text t : this->texts)
	{
		window.draw(t);
	}
}
