#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "StateStack.hpp"
#include "GameContext.hpp"

class StateStack;
class GameContext;

class PauseState : public GameState
{
public:
    PauseState(sf::RenderWindow& window, StateStack& stack, GameContext& context);
    ~PauseState() override;

    void handleInput(const sf::Event& event) override;
    void update(sf::Time delta) override;
    void render() override;

private:
    sf::RenderWindow& window;
    StateStack& stack;
    GameContext& context;

    // 设置初始UI
    sf::Font font;
    // 暂停标题
    sf::Text titleText;
    // 继续按钮
    sf::Text ContinueText;
    sf::RectangleShape ContinueButton;
    // 退出按钮
    sf::Text QuitText;
    sf::RectangleShape QuitButton;
};