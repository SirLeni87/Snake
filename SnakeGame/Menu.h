#pragma once
#include "Button.h"
#include "SinglePlayer.h"
#include "ModifierInfo.h"
#include <iostream>

using namespace std;
using namespace sf;

class Menu
{
public:
	Menu();
	void menu();

private:
	void switchButtons();
	void draw(RenderWindow&);

	vector<cb::Button> buttonSet1;
	vector<cb::Button> buttonSet2;
	RenderWindow window;
	Sprite menuBackground;
};

