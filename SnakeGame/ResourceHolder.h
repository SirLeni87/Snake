#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class ResourceHolder
{
public:
	static void insertTexture(std::string, std::string);
	static sf::Texture& loadTexture(std::string);
	static void insertFont(std::string, std::string);
	static sf::Font& loadFont(std::string);

private:
	static std::map<std::string, sf::Texture> textures;
	static std::map<std::string, sf::Font> fonts;
};

