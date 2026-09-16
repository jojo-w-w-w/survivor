#pragma once
#include <memory>
#include <vector>

class Player;
class EnemyBase;
class Bullet;
//class ResourceManager;

struct GameContext
{
    std::unique_ptr<Player> player;

    std::vector<std::unique_ptr<EnemyBase>> enemies;

    //创建子弹容器
    std::vector<std::unique_ptr<Bullet>> bullets;

    //std::unique_ptr<ResourceManager> textureManager;

    GameContext();
    ~GameContext();
};