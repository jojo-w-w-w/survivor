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
        sf::Vector2f position, float speed, 
        float scale, int expvalue
    );
    virtual ~EnemyBase() = default;

    //敌人都需要实现的行为
    virtual void update(float dt, Player& player);          //更新位置
    virtual void render(sf::RenderWindow& window) const;    //绘制

    virtual bool isActive() const ;                          //检测是否存活
    virtual sf::FloatRect getBound() const ;                 //碰撞检测
    virtual void deActive();                                //消失
    virtual sf::Vector2f getPosition() const;               //获取位置
    virtual int getExp() const;   
    
private:
    //敌人图片
    std::shared_ptr<sf::Texture> texture; //敌人纹理
    sf::Sprite sprite;  //敌人
    //动画
    Animation walkAnimation;
    int facingRow{0};

    float EnemySpeed;
    bool active;
    int ExpValue;

};