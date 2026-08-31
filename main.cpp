#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <memory>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>
#include <cstdlib>
#include "Player.hpp"
#include "EnemyBase.hpp"
#include "Enemy.hpp"
#include "EnemyFactory.hpp"
#include "Bullet.hpp"
#include "Upgrade.hpp"
#include "GameState.hpp"
#include "StateStack.hpp"
#include "MenuState.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1280,720}), "Roguelike Survivor");//设置游戏窗口
    if (!window.isOpen()) //如果窗口打开失败
    {
        std::cerr << "Failed to create window" << std::endl;
        return 1;
    }

    window.setFramerateLimit(60);               //设置帧率为60

    GameContext context;
    StateStack stack;
    //设置初始状态为菜单
    stack.changeState(std::make_unique<MenuState>(window, stack, context));

    sf::Clock clock;

    Player player;                              //先创建一个玩家对象
    
    //创建敌人容器
    std::vector<std::unique_ptr<EnemyBase>> enemies;
    float spawnTimer = 0.f;                     //生成敌人的时间
    const float spawnInterval = 2.f;            //每两秒生成一个敌人

    //创建子弹容器
    std::vector<std::unique_ptr<Bullet>> bullets;

    while(window.isOpen())
    {
        // 事件处理
        while(const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            stack.handleInput(*event);  // 转发给当前状态
        }
        // 更新
        stack.update(clock.restart());
        // 渲染
        window.clear();
        stack.render();
        window.display();
    }
    std::cout << "Game Over!" << std::endl;
    return 0;

    // while (window.isOpen())//渲染事件
    // {
	//     sf::Time dt = clock.restart();
	//     float deltaTime = dt.asSeconds();

   
            
    //         // 菜单状态下检测鼠标点击
    //         if (gamestate == Gamestate::Menu && event.type == sf::Event::MouseButtonPressed) 
    //         {
    //             if (event.mouseButton.button == sf::Mouse::Left) 
    //             {
    //                 sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    //                 if (startButton.getGlobalBounds().contains(mousePos)) 
    //                 {
    //                     // 切换到游戏状态，并重置游戏数据
    //                     gamestate = Gamestate::Playing;
    //                     player.reset();
    //                     enemies.clear();
    //                     bullets.clear();
    //                     spawnTimer = 0.f;
    //                 }
    //             }
    //         } 
    //     //如果当前的游戏状态为游玩
    //     if(gamestate == Gamestate::Playing)
    //     {
            
    //         player.update(deltaTime);//更新玩家状态

    //         //如果玩家此时可以发射子弹
    //         if(player.canshoot(deltaTime))
    //         {
    //             //遍历所有活着的敌人找到最近的
    //             const EnemyBase* nearstEnemy = nullptr;
    //             float minDistance = std::numeric_limits<float>::max();//将最小距离初始化为极大值方便更新
    //             for(const auto& enemy : enemies)
    //             {
    //                 //如果敌人死亡就跳过
    //                 if(!enemy->isActive())
    //                     continue;

    //                 //获得该敌人与玩家之间的坐标差，为了下面计算该敌人与玩家之间的距离
    //                 sf::Vector2f diff = enemy->getPosition() - player.getPosition();

    //                 //计算该敌人与玩家之间的距离
    //                 float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    //                 //更新最小距离
    //                 if(dist < minDistance)
    //                 {
    //                     minDistance = dist;
    //                     nearstEnemy = enemy.get();//更新最近敌人指针
    //                 }
    //             }

    //             //如果找到敌人就发射子弹
    //             if(nearstEnemy != nullptr)
    //             {
    //                 sf::Vector2f direction = nearstEnemy->getPosition() - player.getPosition();
    //                 float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    //                 if(len > 0)
    //                     direction /= len;//归一化

    //                  // 基础方向角度
    //                 float baseAngle = std::atan2(direction.y, direction.x);

    //                 float spread = 0.15f;  // 散射弧度，约 8.6 度

    //                 int bulletCount = player.getBulletCount();   // 需要添加这个公有方法
    //                 for (int i = 0; i < bulletCount; ++i) 
    //                 {
    //                     float angle = baseAngle;
    //                     if (bulletCount > 1) 
    //                     {
    //                         float offset = spread * (i - (bulletCount - 1.0f) / 2.0f);
    //                         angle += offset;
    //                     }
                    
    //                     sf::Vector2f bulletDir(std::cos(angle), std::sin(angle));

    //                     bullets.push_back(std::make_unique<Bullet>());                                 //向子弹数组里添加子弹
    //                     bullets.back()->launch(player.getPosition(), bulletDir, player.getBulletSpeed()); //将子弹的状态设为激活
    //                 }
    //             }
    //         }

    //         //敌人生成
    //         spawnTimer += deltaTime;
    //         if(spawnTimer >= spawnInterval)
    //         {
    //             spawnTimer = 0.f;
    //             enemies.push_back(EnemyFactory::creatRandom());
    //         }

    //         //更新所有敌人
    //         for(auto& enemy : enemies)
    //         {
    //             enemy->update(deltaTime, player.getPosition());
    //         }

    //         //更新所有子弹
    //         for(auto& bullet : bullets)
    //         {
    //             if(bullet->isActive())
    //             {
    //                 bullet->update(deltaTime);
    //             }
    //         }
                    
    //         //清理失效的子弹
    //         bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const std::unique_ptr<Bullet>&b)
    //         {
    //             return !b->isActive();
    //         }), bullets.end());

  
    //     window.clear(sf::Color::Black);        
    //     window.display();
    // }
}
