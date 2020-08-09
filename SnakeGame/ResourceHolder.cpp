#include "ResourceHolder.h"



ResourceHolder::ResourceHolder()
    : textures()
{
}

sf::Texture& ResourceHolder::getTexture(std::string path)
{
    auto pairFound = textures.find(path);
    if (pairFound != textures.end()) {

        return pairFound->second;
    }
    else
    {
        auto& texture = textures[path];
        texture.loadFromFile(path);
        return texture;
    }
}

sf::Font& ResourceHolder::getFont(std::string path)
{
    auto pairFound = fonts.find(path);
    if (pairFound != fonts.end()) {

        return pairFound->second;
    }
    else
    {
        auto& font = fonts[path];
        font.loadFromFile(path);
        return font;
    }
}