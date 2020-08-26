#pragma once
#include "Board.h"

class PvP
{
public:
	PvP();

private:
	void initialize(Board&, Snake&, Snake&, Food&, Food&, bool&);
	bool checkCollision(Board&, Snake&, Food&, bool&, bool = false);
	void checkBuffStatus(Board&, Snake&, Snake&, std::vector<Buff>&, bool = false);
	void move(Snake&, bool&);
	BuffName randomizeBuff();
	sf::Vector2f randomizePosition(bool = false);
	void updateCords(Board, Snake, Snake, Food, Food, std::vector<Buff>, std::vector<Buff>);
	bool checkCollision(sf::Vector2f);

	std::vector<sf::Vector2f> takenCords;
};

