#pragma once
#include "Food.h"
#include <string>

enum class BuffName
{
	obstacle,
	cut,
	noCollision,
	swap
};

class Buff : public Food
{
public:
	Buff(BuffName, sf::Vector2f);
	BuffName getBuffName();

private:
	BuffName name;
};

