#include <iostream>
#include "Enemy.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Player.hpp"

Enemy::Enemy(sf::Vector2f startPosition) : 
texture(ResourceManager::getTexture("assets/RegularEnemy.png")), 
sprite(*texture), enemy_speed(100.f), active(true), expValue(5)
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

void Enemy::update(float dt, Player& player)
{
    sf::Vector2f direction = player.getPosition() - sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if(length > 0)
        direction /= length;

    sprite.move(direction * enemy_speed * dt);
}

void Enemy::render(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

bool Enemy::isActive() const
{
    return active;
}

sf::FloatRect Enemy::getBound() const
{
    return sprite.getGlobalBounds();
}

void Enemy::deActive()
{
    active = false;
}

sf::Vector2f Enemy::getPosition() const
{
    return sprite.getPosition();
}

int Enemy::getExp() const
{
    return expValue;
}