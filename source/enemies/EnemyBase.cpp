#include <iostream>
#include "EnemyBase.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "ResourceManager.hpp"

EnemyBase::EnemyBase
(
    const std::string& texturePath, 
    sf::Vector2f position, float speed, 
    float scale, int expvalue
) :
texture(ResourceManager::getTexture(texturePath)), 
sprite(*texture), walkAnimation({256, 256}, 6, 0.12f), 
facingRow(0), 
EnemySpeed(speed), active(true), ExpValue(expvalue)
{
    // 设置初始动画帧
    walkAnimation.reset(sprite, facingRow);

    // 以当前帧的中心作为精灵原点
    const sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });

    // 设置大小和出生位置
    sprite.setScale({scale, scale});
    sprite.setPosition(position);
}

void EnemyBase::update(float dt, Player& player)
{
    sf::Vector2f direction = player.getPosition() - sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    const bool isMoving = length > 0.f;

    if(isMoving)
    {
        direction /= length;

        if(std::abs(direction.x) > std::abs(direction.y))
        {
            // 左边是第1行，右边是第2行
            facingRow = direction.x < 0.f ? 1 : 2;
        }
        else
        {
            // 上边是第3行，下边是第0行
            facingRow = direction.y < 0.f ? 3 : 0;
        }

        sprite.move(direction * EnemySpeed * dt);
    }

    walkAnimation.update
    (
        sprite,
        dt,
        facingRow,
        isMoving
    );
}

void EnemyBase::render(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

bool EnemyBase::isActive() const
{
    return active;
}

sf::FloatRect EnemyBase::getBound() const
{
    return sprite.getGlobalBounds();
}

void EnemyBase::deActive()
{
    active = false;
}

sf::Vector2f EnemyBase::getPosition() const
{
    return sprite.getPosition();
}

int EnemyBase::getExp() const
{
    return ExpValue;
}