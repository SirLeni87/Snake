#pragma once
#include "Board.h"
#include "Button.h"
#include "Menu.h"

using namespace sf;
using namespace std;

class SinglePlayer
{
public:
	SinglePlayer();
	bool play(float);

private:
	void initialize(Board&, Snake&, Food&, bool&);
	bool checkCollision(Board&, Snake&, Food&, bool&);
	void move(Snake&, bool&);
	bool endGame(RenderWindow&, Event&, bool);
	bool endLoop(RenderWindow&, Event&);

	vector<cb::Button> buttonSet;
	RectangleShape loseScreen;
	RectangleShape winScreen;
	Image icon;
	Text loseText;
	Text winText;
	Text segmentCount;
};

