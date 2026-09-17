#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <string>

class ResourceManager
{
public:
    static std::shared_ptr<sf::Texture> getTexture(const std::string& path);

    static std::shared_ptr<sf::Font> getFont(const std::string& path);

private:
    static std::map<std::string, std::shared_ptr<sf::Texture>> textureCache;

    static std::map<std::string, std::shared_ptr<sf::Font>> fontCache;

};