#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Player;

class EnemyBase
{
public:
    virtual ~EnemyBase() = default;

    //敌人都需要实现的行为
    virtual void update(float dt, Player& player) = 0;          //更新位置
    virtual void render(sf::RenderWindow& window) const = 0;    //绘制

    virtual bool isActive() const = 0;                          //检测是否存活
    virtual sf::FloatRect getBound() const = 0;                 //碰撞检测
    virtual void deActive() = 0;                                //消失
    virtual sf::Vector2f getPosition() const = 0;               //获取位置
    virtual int getExp() const = 0;    
};