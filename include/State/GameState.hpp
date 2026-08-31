#pragma once
#include <SFML/Graphics.hpp>

class GameState 
{
public:
    virtual ~GameState() = default;

    // 处理事件，比如按键、鼠标
    virtual void handleInput(const sf::Event& event) = 0;

    // 更新逻辑（每一帧调用）
    virtual void update(sf::Time delta) = 0;
    
    // 渲染（每一帧调用）
    virtual void render() = 0;
};