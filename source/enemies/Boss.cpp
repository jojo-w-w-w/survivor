#include <iostream>
#include "Boss.hpp"
#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>
#include "Player.hpp"

Boss::Boss(sf::Vector2f startPosition) : 
texture(ResourceManager::getTexture("assets/Boss.png")), 
sprite(*texture), walkAnimation({256, 256}, 6, 0.12f), 
enemy_speed(100.f), active(true), expValue(50)
{
    // 像素画禁止平滑
    texture->setSmooth(false);

    // 显示第0列、第0行，也就是左上角第一格
    sprite.setTextureRect
    (
        sf::IntRect({0, 0}, {256, 256})
    );

    sprite.setScale({0.75f,0.75f});

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    sprite.setPosition(startPosition);//设置敌人出现的初始位置
}

void Boss::update(float dt, Player& player)
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

        sprite.move(direction * enemy_speed * dt);
    }

    walkAnimation.update
    (
        sprite,
        dt,
        facingRow,
        isMoving
    );
}

void Boss::render(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

bool Boss::isActive() const
{
    return active;
}

sf::FloatRect Boss::getBound() const
{
    return sprite.getGlobalBounds();
}

void Boss::deActive()
{
    active = false;
}

sf::Vector2f Boss::getPosition() const
{
    return sprite.getPosition();
}

int Boss::getExp() const
{
    return expValue;
}