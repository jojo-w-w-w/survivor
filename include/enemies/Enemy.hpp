#pragma once
#include <SFML/Graphics.hpp>
#include "EnemyBase.hpp"
#include "ResourceManager.hpp"

class Enemy : public EnemyBase
{
public:
    //敌人状态
    Enemy();                                                 //初始化敌人
    void update(float dt, sf::Vector2f playerPos) override;  //更新敌人位置
    void render(sf::RenderWindow& window) const override;    //绘制敌人

    //敌人行为
    bool isActive() const override;                          //检测敌人是否存活
    sf::FloatRect getBound() const override;                 //碰撞检测
    void deActive() override;                                //让敌人消失
    sf::Vector2f getPosition() const override;               //获取敌人位置
    int getExp() const override;

private:
//敌人状态

    //敌人图片
    std::shared_ptr<sf::Texture> texture;                 //敌人纹理
    sf::Sprite sprite;  //敌人

    float enemy_speed;
    bool active;                                         //用来标记敌人是否存活
    int expValue;                                        //当前怪物所包含的经验值

    
};