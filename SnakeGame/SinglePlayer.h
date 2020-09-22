#pragma once
#include "Board.h"
#include "Button.h"
#include "Menu.h"

class SinglePlayer
{
public:
	SinglePlayer(float);

private:
	void initialize(Board&, Snake&, Food&, bool&);
	bool checkCollision(Board&, Snake&, Food&, bool&);
	void move(Snake&, bool&);
};

