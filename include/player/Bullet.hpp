#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
    //初始化子弹
    Bullet();                                                              //构造函数：
    void launch(sf::Vector2f startPos, sf::Vector2f direction, float bulletSpeed);            //子弹发射
    void update(float dt);                                                 //更新子弹的位置函数
    void render(sf::RenderWindow& window) const;                           //绘制子弹

    //子弹状态
    bool isActive() const;                          //检测子弹是否存在
    sf::FloatRect getBound() const;                 //碰撞检测
    void deActive();                                //让子弹消失

private:

    //子弹图片
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2f velocity;  //归一化的方向
    float Bullet_speed;
    bool active;            //检测子弹是否存在
};