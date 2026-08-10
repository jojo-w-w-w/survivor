#include <iostream>
#include "Bullet.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>

Bullet::Bullet() : Bullet_speed(400.f), active(false)//只有玩家存活时才有子弹
{
    if(!texture.loadFromFile("assets/bullet.png"))
    {
        std::cerr << "Faild to load bullet txture" << std::endl;
    }
    sprite.setTexture(texture);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);                 //设置子弹的中心

}

void Bullet::launch(sf::Vector2f startPos, sf::Vector2f direction, float bulletSpeed)
{
    sprite.setPosition(startPos);//设置子弹的初始位置，应该与玩家位置相同

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    velocity = (length > 0) ? direction / length : sf::Vector2f(0,0);

    this->Bullet_speed = bulletSpeed;

    active = true;//调用launch之后子弹被射出所以改变子弹的状态
}

void Bullet::update(float dt)
{
    //若子弹消失则返回
    if(!active)
        return;

    sprite.move(velocity * Bullet_speed * dt);

    //子弹的位置
    sf::Vector2f pos = sprite.getPosition();
    //子弹飞出边界后消失
    if(pos.x < -10.f || pos.x > 1290.f || pos.y < -10.f || pos.y > 730.f)
        active = false;
   
}

void Bullet::render(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

bool Bullet::isActive() const
{
    return active;
}

sf::FloatRect Bullet::getBound() const
{
    return sprite.getGlobalBounds();
}

void Bullet::deActive()
{
    active = false;
}