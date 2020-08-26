#pragma once
#include "Board.h"

class SinglePlayer
{
public:
	SinglePlayer();

private:
	void initialize(Board&, Snake&, Food&, bool&);
	bool checkCollision(Board&, Snake&, Food&, bool&);
	void move(Snake&, bool&);
};

