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
