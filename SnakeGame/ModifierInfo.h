#pragma once
#include "PvP.h"

class ModifierInfo
{
public:
	ModifierInfo();
	void showInfo();

private:
	void draw(RenderWindow&);

	PvP pvp;

	sf::Sprite background;
	Image icon;
	cb::Button startButton;
	std::vector<sf::Sprite> sprites;
	std::vector<sf::Text> texts;
};

