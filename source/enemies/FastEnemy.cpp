#include <iostream>
#include "FastEnemy.hpp"
#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>

FastEnemy::FastEnemy() : enemy_speed(150.f), active(true), expValue(10)
{
    texture = ResourceManager::getTexture("assets/fastenemy.png");
    sprite.setTexture(*texture);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

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

    sprite.setPosition(x, y);//设置敌人出现的初始位置
}

void FastEnemy::update(float dt, sf::Vector2f playerPos)
{
    sf::Vector2f direction = playerPos - sprite.getPosition();

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