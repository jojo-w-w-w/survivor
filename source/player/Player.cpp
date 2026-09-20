#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "ResourceManager.hpp"

Player::Player(sf::Vector2f startPosition) : 
texture(ResourceManager::getTexture("assets/Player.png")), 
sprite(*texture), player_speed(200.f), maxHp(5),
hp(5), shootTimer(0.f), shootCooldown(1.f), 
bulletSpeed(400.f), bulletCount(1), exp(0), 
expToNextLevel(10), level(1), 
pendingLevelUps(0)
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
    sprite.setPosition(startPosition);//将玩家移动到窗口中心

}

// void Player::update(float dt)
// {
    
// }

void Player::move(sf::Vector2f direction, float delta)
{
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if(length > 0)
        direction /= length;
        
    sprite.move(direction * player_speed * delta);
}

void Player::render(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() const
{
    return sprite.getPosition();
}

sf::FloatRect Player::getBound() const
{
    return sprite.getGlobalBounds();
}

int Player::getHP() const
{
    return hp;
}

bool Player::isDead() const
{
    return hp <= 0;
}

void Player::isDamage(int damage)
{
    hp -= damage;
    if(hp < 0)
    {
        hp = 0;
    }
}

void Player::updateShootTimer(float dt)
{
    if(shootTimer < shootCooldown)
    {
        shootTimer += dt;
    }
}

bool Player::canShoot() const
{
   if(shootTimer >= shootCooldown)
   {
        return true;
   }
   return false;
}

void Player::resetShootTimer()
{
    shootTimer = 0.f;
}

void Player::addExp(int amount)
{
    exp += amount;
    while(exp >= expToNextLevel)
    {
        exp -= expToNextLevel;
        level++;
        //下一次升级所需求的经验值增长
        expToNextLevel = static_cast<int>(expToNextLevel * 1.3f);
        ++pendingLevelUps;
    }
}

int Player::getExp() const
{
    return exp;
}

int Player::getLevel() const
{
    return level;
}

bool Player::justLevelUp()
{
    if(pendingLevelUps > 0)
    {
        --pendingLevelUps;
        return true;
    }
    return false;
}