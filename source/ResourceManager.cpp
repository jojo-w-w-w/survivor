#include <iostream>
#include "ResourceManager.hpp"

std::map<std::string, std::weak_ptr<sf::Texture>> ResourceManager::textureCache;

std::shared_ptr<sf::Texture> ResourceManager::getTexture(const std::string& path)
{
    auto it = textureCache.find(path);
    if(it != textureCache.end())
    {
        if(auto tex = it->second.lock())
        {
            return tex;
        }
    }
    auto newTexture = std::make_shared<sf::Texture>();
    if(!newTexture->loadFromFile(path))
    {
        std::cerr << "Failed to load texture: " << path <<std::endl;
    }
    textureCache[path] = newTexture;
    return newTexture;
}
