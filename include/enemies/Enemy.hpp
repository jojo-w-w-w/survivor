#pragma once
#include <SFML/Graphics.hpp>
#include "EnemyBase.hpp"

class Enemy : public EnemyBase
{
public:
    //敌人状态
    Enemy(sf::Vector2f position); //初始化敌人
};