#pragma once
#include <SFML/Graphics.hpp>
#include <memory.h>
#include "Player.hpp"
#include "EnemyBase.hpp"
#include "Bullet.hpp"
#include "PauseState.hpp"
#include "ResourceManager.hpp"

class Player;
class EnemyBase;
class Bullet;
class ResourceManager;

struct GameContext
{
    std::unique_ptr<Player> player;

    std::vector<std::unique_ptr<EnemyBase>> enemies;

    //创建子弹容器
    std::vector<std::unique_ptr<Bullet>> bullets;

    std::unique_ptr<ResourceManager> textureManager;

    GameContext();
};