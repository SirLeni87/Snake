#include "Buff.h"

Buff::Buff(BuffName name, sf::Vector2f pos)
{
	if (name == BuffName::obstacle)
		this->sprite.setTexture(ResourceHolder::loadTexture("shrimp"));
	else if(name == BuffName::cut)
		this->sprite.setTexture(ResourceHolder::loadTexture("pufferfish"));
	else if(name == BuffName::noCollision)
		this->sprite.setTexture(ResourceHolder::loadTexture("jellyfish"));
	else if(name == BuffName::swap)
		this->sprite.setTexture(ResourceHolder::loadTexture("whirlpool"));

	this->sprite.setScale(0.5, 0.5);
	this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2.f, this->sprite.getLocalBounds().height / 2.f);

	this->name = name;

	this->sprite.setPosition(pos);
}

BuffName Buff::getBuffName()
{
	return this->name;
}
