#pragma once
#include "Segment.h"

class Head : public Segment
{
public:
	Head();
	static sf::Texture& getTexture();
	static void setSegmentTexture(std::string);

private:
	static sf::Texture* texture;
};

