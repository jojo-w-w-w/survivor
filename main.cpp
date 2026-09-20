#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <memory>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <exception>
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
    try
    {
        //设置游戏窗口
        const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        sf::RenderWindow window
        (
            desktopMode,
            "Roguelike Survivor",
            sf::State::Fullscreen
        );
        
        window.setFramerateLimit(60);               //设置帧率为60

        GameContext context;

        // 获取实际全屏尺寸
        const auto size = window.getSize();

        context.screenSize  = 
        {
            static_cast<float>(size.x),
            static_cast<float>(size.y)
        };

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
    catch(const std::exception& error)
    {
        std::cerr << "Fatal error: " << error.what() << '\n';
        return 1;
    }
}