#pragma once
#include "Segment.h"

class Tail : public Segment
{
public:
	Tail();
	static sf::Texture& getTexture();
	static void setSegmentTexture(std::string);

private:
	static sf::Texture* texture;
};

