#include <iostream>
#include "Boss.hpp"
#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>

Boss::Boss() : texture(ResourceManager::getTexture("assets/danouboss.jpg")), sprite(*texture), enemy_speed(100.f), active(true), expValue(50)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> edgeDist(0,3);
    int edge = edgeDist(gen);

    const float WIDTH = 1280.f;
    const float HEIGHT = 720.f;

    std::uniform_real_distribution<float> xDist(0.f, WIDTH);
    std::uniform_real_distribution<float> yDist(0.f, HEIGHT);
    float x = 0.f, y = 0.f;

    switch (edge) 
    {
        case 0: // 上边缘
            x = xDist(gen);
            y = 0.f;
            break;
        case 1: // 下边缘
            x = xDist(gen);
            y = HEIGHT;
            break;
        case 2: // 左边缘
            x = 0.f;
            y = yDist(gen);
            break;
        case 3: // 右边缘
            x = WIDTH;
            y = yDist(gen);
            break;
    }

    sprite.setPosition({x, y});//设置敌人出现的初始位置
}

void Boss::update(float dt, Player& player)
{
    sf::Vector2f direction = player.getPosition() - sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if(length > 0)
        direction /= length;

    sprite.move(direction * enemy_speed * dt);
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