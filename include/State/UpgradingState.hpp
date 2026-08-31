#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "StateStack.hpp"
#include "GameContext.hpp"
#include "PlayingState.hpp"
#include "Upgrade.hpp"

class UpgradingState : public GameState
{
public:
    UpgradingState(sf::RenderWindow& window, StateStack& stack, GameContext& context);
    ~UpgradingState() override;

    void handleInput(const sf::Event& event) override;
    void update(sf::Time delta) override;
    void render() override;

private:
    sf::RenderWindow& window;
    StateStack& stack;
    GameContext& context;

    // 设置更新界面背景图片
    sf::Texture MenuBgTexture;
    sf::Sprite MenuBgSprite;

    // 升级选项总数
    std::vector<Upgrade> UpgradeOption;
    // 设置更新UI
    sf::Font font;
    // 半透明黑色遮罩
    sf::RectangleShape overlay;
    // 绘制标题
    sf::Text title;
    // 单个选项
    std::vector<sf::Text> optionTexts;
       

    
};