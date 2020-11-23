#include "ResourceHolder.h"

std::map<std::string, sf::Texture> ResourceHolder::textures;
std::map<std::string, sf::Font> ResourceHolder::fonts;

void ResourceHolder::insertTexture(std::string name, std::string path)
{
	sf::Texture newTexture;

	for (int i = 0;; i++)
	{
		if (newTexture.loadFromFile(path))
		{
			break;
		}
		else if (i >= 4)
		{
			std::cout << "Could not load a texture!" << std::endl;
			exit(1);
		}
	}

	textures.insert(std::pair<std::string, sf::Texture>(name, newTexture));
}

sf::Texture& ResourceHolder::loadTexture(std::string name)
{
	auto toFind = textures.find(name);

	if (toFind == textures.end())
	{
		std::cout << "Could not find a texture!" << std::endl;
		exit(2);
	}

	return textures[name];
}

void ResourceHolder::insertFont(std::string name, std::string path)
{
	sf::Font newFont;

	for (int i = 0;; i++)
	{
		if (newFont.loadFromFile(path))
		{
			break;
		}
		else if (i >= 4)
		{
			std::cout << "Could not load a font!" << std::endl;
			exit(1);
		}
	}

	fonts.insert(std::pair<std::string, sf::Font>(name, newFont));
}

sf::Font& ResourceHolder::loadFont(std::string name)
{
	auto toFind = fonts.find(name);

	if (toFind == fonts.end())
	{
		std::cout << "Could not find a texture!" << std::endl;
		exit(2);
	}

	return fonts[name];
}
