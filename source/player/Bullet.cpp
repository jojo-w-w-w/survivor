#include "Bullet.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>

Bullet::Bullet() : 
texture(ResourceManager::getTexture("assets/Bullet.png")), 
sprite(*texture), animation({220, 220}, 8, 0.08f, {8, 342}),
Bullet_speed(400.f), active(false)//只有玩家存活时才有子弹
{
    // 像素画禁止平滑
    texture->setSmooth(false);

    animation.reset(sprite, 0);

    centerOrigin();

    sprite.setScale({0.25f,0.25f});

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin
    ({
        bounds.size.x / 2.f, 
        bounds.size.y / 2.f
    });//设置子弹的中心
}

void Bullet::launch(sf::Vector2f startPos, sf::Vector2f direction, float bulletSpeed)
{
    animation.reset(sprite, 0);

    centerOrigin();

    sprite.setPosition(startPos);//设置子弹的初始位置，应该与玩家位置相同

    float length = std::sqrt
    (
        direction.x * direction.x + 
        direction.y * direction.y
    );

    velocity = (length > 0) ? direction / length : sf::Vector2f(0,0);

    this->Bullet_speed = bulletSpeed;

    active = true;//调用launch之后子弹被射出所以改变子弹的状态
}

void Bullet::update(float dt, sf::Vector2f screenSize)
{
    //若子弹消失则返回
    if(!active)
        return;

    animation.update(sprite, dt, 0, true);

    sprite.move(velocity * Bullet_speed * dt);

    //子弹的位置
    sf::Vector2f pos = sprite.getPosition();
    constexpr float margin = 32.f;
    //子弹飞出边界后消失
    if(pos.x < -margin || pos.x > screenSize.x + margin || pos.y < -margin || pos.y > screenSize.y + margin)
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

void Bullet::centerOrigin()
{
    const sf::FloatRect bounds = sprite.getLocalBounds();

    sprite.setOrigin
    ({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });
}