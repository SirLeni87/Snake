#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ResourceHolder
{
public:
	ResourceHolder();
    sf::Texture& getTexture(std::string path);
    sf::Font& getFont(std::string path);

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};

