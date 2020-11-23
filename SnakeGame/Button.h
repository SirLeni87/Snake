#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

namespace custom_button
{

	class Button
	{
	private:
		RectangleShape button;
		Text text;
		bool active = true;

	public:
		Button(Vector2f position, Vector2f size, Color fillColor, float outlineThickness = 0, Color outlineColor = Color(0, 0, 0, 0), String text = "", Vector2f textPosition = Vector2f(0, 0), int textSize = 30);
		void draw(RenderWindow& window);
		bool isMouseOver(RenderWindow& window);
		void setFont(Font&);
		void setColor(Color);
		void setActive(bool);
		bool getActiveStatus();
	};

}

namespace cb = custom_button;

