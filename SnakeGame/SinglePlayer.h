#pragma once
#include "Board.h"
#include <thread>

class SinglePlayer
{
public:
	SinglePlayer();

private:
	void initialize(Board&, Snake&, Food&, bool&);
	void checkCollision(Board&, Snake&, Food&);
	void move(Snake&);
};

