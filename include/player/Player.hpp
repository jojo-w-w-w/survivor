#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"
#include "MenuState.hpp"
#include "PlayingState.hpp"

struct Upgrade;

class Player 
{
public:
    //初始化玩家
    Player();                                      // 构造函数：初始化形状、速度等
    void update(float dt);                         // 处理动画、状态更新
    void move(sf::Vector2f direction, float delta);// 处理移动
    void render(sf::RenderWindow& window) const;   // 绘制玩家

    //玩家状态
    sf::Vector2f getPosition() const;
    sf::FloatRect getBound() const;                 //碰撞检测
    int getHP() const;                              //获取玩家当前血量
    bool isDead() const;                            //判断玩家是否死亡
    void isDamage(int damage);                      //判断玩家是否受伤

    void reset();                                   //重置玩家状态S

//玩家行为:

    //发射子弹
    bool canshoot(float dt);

    //升级
    void addExp(int amount);
    int  getExp() const;
    int  getLevel() const;
    bool justLevelUp();                            //检测上一帧是否升级
    int  getMaxHp() const { return maxHp; }
    int  getExpToNext() const { return expToNextLevel; }

    //可以升级的部分
    void reduceShootCooldown(float factor) { shootCooldown *= factor; }
    void increaseSpeed(float factor)       { player_speed *= factor; }
    void increaseMaxHp(int amount)         { maxHp += amount; hp += amount; }
    void increaseBulletSpeed(float factor) { bulletSpeed *= factor; }
    void increaseBulletCount(int amount)   { bulletCount += amount; }

    float getBulletSpeed() const { return bulletSpeed; }
    int getBulletCount() const { return bulletCount; }


private:
//玩家状态

    //玩家图片
    std::shared_ptr<sf::Texture> texture;//玩家纹理
    sf::Sprite sprite; //玩家

    float player_speed;
    int maxHp;
    int hp;

//玩家行为：

    //射击
    float shootTimer;                               //射击冷却计时器
    float shootCooldown;                            //射击冷却
    float bulletSpeed;      
    int bulletCount;

    //升级
    int exp;
    int expToNextLevel;
    int level;
    int pendingLevelUps{0};                         //标记需要处理的升级次数

};