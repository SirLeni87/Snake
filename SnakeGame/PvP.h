#pragma once
#include "Board.h"
#include "Button.h"
#include "Menu.h"

class PvP
{
public:
	PvP();

private:
	void initialize(Board&, Snake&, Snake&, Food&, Food&, Missle&, Missle&,bool&);
	bool checkCollision(Board&, Snake&, Food&, bool&, bool = false);
	void checkBuffStatus(Board&, Snake&, Snake&, std::vector<Buff>&, bool = false);
	void shootMissle(RenderWindow&, Board&, Missle&, Snake&, Snake&, bool&);
	void move(Snake&, bool&, bool = false);
	BuffName randomizeBuff();
	sf::Vector2f randomizePosition(bool = false);
	void updateCords(Board, Snake, Snake, Food, Food, std::vector<Buff>, std::vector<Buff>);
	bool checkCollision(sf::Vector2f);

	std::vector<sf::Vector2f> takenCords;
	bool swapped = false;
	float speedUpMod = 0;
};

