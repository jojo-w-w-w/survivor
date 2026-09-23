#pragma once
#include <SFML/Graphics.hpp>
#include "EnemyBase.hpp"

class Boss : public EnemyBase
{
public:
    //敌人状态
    Boss(sf::Vector2f startPosition);                                                  //初始化敌人
   
};