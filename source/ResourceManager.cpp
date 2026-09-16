#include <stdexcept>
#include "ResourceManager.hpp"

std::map<std::string, std::shared_ptr<sf::Texture>> ResourceManager::textureCache;

std::shared_ptr<sf::Texture> ResourceManager::getTexture(const std::string& path)
{
    auto it = textureCache.find(path);
    if(it != textureCache.end())
    {
        return it->second;
    }

    auto newTexture = std::make_shared<sf::Texture>();
    if(!newTexture->loadFromFile(path))
    {
        throw std::runtime_error
        (
            std::string("Failed to load texture: ") + path
        );
    }
    textureCache[path] = newTexture;
    return newTexture;
}
