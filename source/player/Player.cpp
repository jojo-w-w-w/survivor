#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "MenuState.hpp"
#include "PlayingState.hpp"

Player::Player() : texture(ResourceManager::getTexture("assets/player.png")), 
                   sprite(*texture), player_speed(200.f), maxHp(5),
                   hp(5), shootTimer(0.f), shootCooldown(1.f),
                   bulletSpeed(400.f), bulletCount(1), exp(0), 
                   expToNextLevel(10), level(1), 
                   leveledUpThisFrame(false)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    sprite.setPosition({640.f, 360.f});//将玩家移动到窗口中心

}

void Player::update(float dt)
{
    
}

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

void Player::reset()
{
    player_speed = 200.f;
    maxHp = 5;
    hp = 5;
    shootTimer = 0.f;
    shootCooldown = 1.f;
    bulletSpeed = 400.f;
    bulletCount = 1;
    exp = 0;
    expToNextLevel = 10;
    level = 1;
    leveledUpThisFrame = false;
    
    texture = ResourceManager::getTexture("assets/player.png");
    sprite.setTexture(*texture);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x/ 2.f, bounds.size.y / 2.f});
    sprite.setPosition({640.f, 360.f});//将玩家移动到窗口中心

}

bool Player::canshoot(float dt)
{
    shootTimer += dt;
    //射击计时器的时间大于冷却
    if(shootTimer >= shootCooldown)
    {
        shootTimer = 0.f;               //重置计时器
        return true;                    //通知外部可以射击
    }
    return false;
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
        leveledUpThisFrame = true;
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
    if(leveledUpThisFrame)
    {
        leveledUpThisFrame = false;
        return true;
    }
    return false;
}