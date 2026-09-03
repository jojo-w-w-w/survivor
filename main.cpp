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
}