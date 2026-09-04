#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "StateStack.hpp"
#include "GameContext.hpp"
#include "PlayingState.hpp"

struct GameContext;

class DeadState : public GameState
{
public:
    DeadState(sf::RenderWindow& window, StateStack& stack, GameContext& context);
    ~DeadState() override;

    void handleInput(const sf::Event& event) override;
    void update(sf::Time delta) override;
    void render() override;

private:
    sf::RenderWindow& window;
    StateStack& stack;
    GameContext& context;

    //设置死亡界面背景图片
    sf::Texture DeadBgTexture;
    sf::Sprite DeadBgSprite;
    
    // 设置初始UI
    sf::Font font;
    // 死亡
    sf::Text titleText;
    // 重新开始按钮
    sf::Text reStartText;
    sf::RectangleShape restartButton;
    // 退出至菜单按钮
    sf::Text QuitToMenuText;
    sf::RectangleShape QuitToMenuButton;
    
};