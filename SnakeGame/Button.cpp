#include "Button.h"

using namespace cb;


Button::Button(Vector2f position, Vector2f size, Color fillColor, float outlineThickness, Color outlineColor, String text, Vector2f textPosition, int textSize)
{
	this->button.setPosition(position);
	this->button.setSize(size);
	this->button.setFillColor(fillColor);
	this->button.setOutlineThickness(outlineThickness);
	this->button.setOutlineColor(outlineColor);
	this->text.setString(text);
	this->text.setCharacterSize(textSize);
	this->text.setPosition(textPosition.x, textPosition.y);
	this->text.setFillColor(Color(92, 177, 219));
}

void Button::draw(RenderWindow& window)
{
	if (this->active)
	{
		window.draw(this->button);
		window.draw(this->text);
	}
}

bool Button::isMouseOver(RenderWindow& window)
{
	if (this->active == false)
		return false;

	float mouseX = Mouse::getPosition(window).x;
	float mouseY = Mouse::getPosition(window).y;

	float btnPosX = this->button.getPosition().x;
	float btnPosY = this->button.getPosition().y;

	float btnWidth = btnPosX + button.getLocalBounds().width;
	float btnHeight = btnPosY + button.getLocalBounds().height;

	if (mouseX < btnWidth && mouseX > btnPosX && mouseY < btnHeight && mouseY > btnPosY)
	{
		return true;
	}

	return false;
}

void custom_button::Button::setFont(Font& font)
{
	this->text.setFont(font);
}

void custom_button::Button::setColor(Color newColor)
{
	this->button.setFillColor(newColor);
}

void custom_button::Button::setActive(bool active)
{
	this->active = active;
}

bool custom_button::Button::getActiveStatus()
{
	return this->active;
}


