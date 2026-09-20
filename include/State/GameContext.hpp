#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Player;
class EnemyBase;
class Bullet;
//class ResourceManager;

struct GameContext
{
    sf::Vector2f screenSize{};

    sf::Vector2f getScreenSize() const
    {
        return screenSize;
    }

    sf::Vector2f getScreenCenter() const
    {
        return 
        {
            screenSize.x /2.f,
            screenSize.y /2.f
        };
    }

    std::unique_ptr<Player> player;

    std::vector<std::unique_ptr<EnemyBase>> enemies;

    //创建子弹容器
    std::vector<std::unique_ptr<Bullet>> bullets;

    //std::unique_ptr<ResourceManager> textureManager;

    GameContext();
    ~GameContext();
};