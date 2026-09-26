#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Player.hpp"
#include "ResourceManager.hpp"

Player::Player(sf::Vector2f startPosition) : 
texture(ResourceManager::getTexture("assets/Player.png")), 
sprite(*texture), walkAnimation({256, 256}, 6, 0.12f), 
player_speed(200.f), maxHp(10), hp(10), 
shootTimer(0.f), shootCooldown(1.f), bulletSpeed(400.f), bulletCount(1), 
exp(0), expToNextLevel(10), level(1), pendingLevelUps(0)
{
    // 像素画禁止平滑
    texture->setSmooth(false);

    // 动画
    walkAnimation.reset(sprite, 0);

    sprite.setScale({0.5f,0.5f});

    sf::FloatRect bounds = sprite.getLocalBounds();

    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    sprite.setPosition(startPosition);//将玩家移动到窗口中心

}

void Player::move(sf::Vector2f direction, float delta)
{
    float length = std::sqrt
    (
        direction.x * direction.x + 
        direction.y * direction.y
    );

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

        sprite.move(direction * player_speed * delta);
    }

    walkAnimation.update
    (
        sprite,
        delta,
        facingRow,
        isMoving
    );
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
bool Player::takeDamage(int damage)
{
    //玩家死亡，处于无敌，上一次受伤间隔时间小于可以受伤的时间间隔
    if(isDead() || damage <= 0 || NbTimer > 0.f || DamageIntervalTimer > 0.f)
    {
        return false;
    }
        
    hp -= damage;
    
    if(hp < 0)
    {
        hp = 0;
    }

    //受到伤害，设置间隔
    DamageIntervalTimer = DamageInterval;

    //玩家存活并且可以无敌的冷却时间已好
    if(!isDead() && NbCooldownTimer <= 0.f)
    {
        NbTimer = NbTime;               //无敌的剩余时间等于无敌持续时间
        NbCooldownTimer = NbCooldown;   //无敌的冷却时间设置为默认的无敌冷却时间
    }

    return true;
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

void Player::updateDamageTimers(float dt)
{
    DamageIntervalTimer = std::max(0.f, DamageIntervalTimer- dt);

    NbTimer = std::max(0.f, NbTimer - dt);

    NbCooldownTimer = std::max(0.f, NbCooldownTimer - dt);
}

bool Player::isNB() const
{
    return NbTimer > 0.f;
}

void Player::updateVisual()
{
    if(isNB())
        sprite.setColor(sf::Color(255, 255, 255, 100));
    else
        sprite.setColor(sf::Color::White);
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