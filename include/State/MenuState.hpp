#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "StateStack.hpp"
#include "GameContext.hpp"
#include "PlayingState.hpp"

struct GameContext;

class MenuState : public GameState
{
public:
    MenuState(sf::RenderWindow& window, StateStack& stack, GameContext& context);
    ~MenuState() override;

    void handleInput(const sf::Event& event) override;
    void update(sf::Time delta) override;
    void render() override;

private:
    sf::RenderWindow& window;
    StateStack& stack;
    GameContext& context;

    //设置开始界面背景图片
    sf::Texture MenuBgTexture;
    sf::Sprite MenuBgSprite;
    
    // 设置初始UI
    sf::Font font;
    // 菜单标题
    sf::Text titleText;
    // 开始按钮
    sf::Text StartText;
    sf::RectangleShape startButton;
    // 退出按钮
    sf::Text QuitText;
    sf::RectangleShape QuitButton;
    
};