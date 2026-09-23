#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "Animation.hpp"

class Player;

class EnemyBase
{
public:
    EnemyBase
    (
        const std::string& texturePath, 
        sf::Vector2f position, int HP, float speed, 
        float scale, int expvalue
    );
    virtual ~EnemyBase() = default;

    //敌人都需要实现的行为
    virtual void update(float dt, Player& player);          //更新位置
    virtual void render(sf::RenderWindow& window) const;    //绘制

    virtual bool isActive() const ;                         //检测是否存活
    virtual sf::FloatRect getBound() const ;                //碰撞检测
    int getHP() const;                                      //获取敌人当前血量
    bool isDead() const;                                    //判断敌人是否死亡
    void takeDamage(int damage);                            //判断敌人是否受伤
    virtual sf::Vector2f getPosition() const;               //获取位置
    virtual int getExp() const;   
    
private:
    //敌人图片
    std::shared_ptr<sf::Texture> texture; //敌人纹理
    sf::Sprite sprite;  //敌人
    //动画
    Animation walkAnimation;
    int facingRow{0};

    int hp;

    float EnemySpeed;
    bool active;
    int ExpValue;

};