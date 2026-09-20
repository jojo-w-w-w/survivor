#include <iostream>
#include "FastEnemy.hpp"
#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>
#include "Player.hpp"

FastEnemy::FastEnemy(sf::Vector2f startPosition) : 
texture(ResourceManager::getTexture("assets/FastEnemy.png")), 
sprite(*texture), enemy_speed(150.f), active(true), expValue(10)
{
    // 像素画禁止平滑
    texture->setSmooth(false);

    // 显示第0列、第0行，也就是左上角第一格
    sprite.setTextureRect
    (
        sf::IntRect({0, 0}, {256, 256})
    );

    sprite.setScale({0.5f,0.5f});

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    sprite.setPosition(startPosition);//设置敌人出现的初始位置
}

void FastEnemy::update(float dt, Player& player)
{
    sf::Vector2f direction = player.getPosition() - sprite.getPosition();

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if(length > 0)
        direction /= length;

    sprite.move(direction * enemy_speed * dt);
}

void FastEnemy::render(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

bool FastEnemy::isActive() const
{
    return active;
}

sf::FloatRect FastEnemy::getBound() const
{
    return sprite.getGlobalBounds();
}

void FastEnemy::deActive()
{
    active = false;
}

sf::Vector2f FastEnemy::getPosition() const
{
    return sprite.getPosition();
}

int FastEnemy::getExp() const
{
    return expValue;
}