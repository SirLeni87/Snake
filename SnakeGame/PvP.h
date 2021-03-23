#pragma once
#include "Board.h"
#include "Button.h"

using namespace sf;
using namespace std;

class PvP
{
public:
	PvP();
	bool play();

private:
	void initialize(Board&, Snake&, Snake&, Food&, Food&, Missle&, Missle&,bool&);
	bool checkCollision(Board&, Snake&, Food&, bool&, bool = false);
	void checkBuffStatus(Board&, Snake&, Snake&, std::vector<Buff>&, bool = false);
	void shootMissle(RenderWindow&, Board&, Missle&, Snake&, Snake&, bool&);
	void move(Snake&, bool&, bool = false);
	BuffName randomizeBuff();
	Vector2f randomizePosition(bool = false);
	void updateCords(Board, Snake, Snake, Food, Food, std::vector<Buff>, std::vector<Buff>);
	bool checkCollision(Vector2f);
	bool endLoop(RenderWindow&, Event&);
	void resetEndCords();

	vector<Vector2f> takenCords;
	bool swapped;
	float speedUpMod = 0;

	vector<cb::Button> buttonSet;
	RectangleShape loseScreen;
	RectangleShape winScreen;
	Text loseText;
	Text winText;
	Image icon;

	Sprite leftMissleIndicator;
	Sprite rightMissleIndicator;
	Text segmentCount1;
	Text segmentCount2;
};

