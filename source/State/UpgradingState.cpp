#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>
#include "UpgradingState.hpp"

UpgradingState::UpgradingState(sf::RenderWindow& window, StateStack& stack, GameContext& context) : 
window(window), stack(stack), context(context), MenuBgSprite(MenuBgTexture), title(font)
{
    if(!font.openFromFile("LiberationSans-Bold.ttf"))
    {
        std::cerr << "Failed to load LiberationSans-Bold.ttf, cause UpgradingState.cpp\n" << std::endl;
    }

    overlay.setSize(sf::Vector2f(1280, 720));
    overlay.setFillColor(sf::Color(0, 0, 0, 180)); // 180 是透明度
    
    // 绘制标题
    title.setString("LEVEL UP!");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition({400.f, 100.f});

    //随机抽取三个升级选项
    UpgradeOption.clear();
    optionTexts.clear();
    auto pool = allUpgrades;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pool.begin(), pool.end(), g);
    for(int i = 0; i < 3 && i < static_cast<int>(pool.size()); ++i)
    {
        UpgradeOption.push_back(pool[i]);
        sf::Text text(font);

        text.setString(std::to_string(i+1) + ". " + UpgradeOption[i].name + "\n   " + UpgradeOption[i].description);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setPosition({200.f, 250.f + i * 120.f});
        optionTexts.push_back(text);
    }
    
}

UpgradingState::~UpgradingState() = default;

void UpgradingState::handleInput(const sf::Event& event)
{
    if(const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        int choice = -1;

        if(keyPressed->code == sf::Keyboard::Key::Num1) 
            choice = 0;

        else if(keyPressed->code == sf::Keyboard::Key::Num2) 
            choice = 1;

        else if(keyPressed->code == sf::Keyboard::Key::Num3) 
            choice = 2;

        if(choice >= 0 && choice < UpgradeOption.size()) 
        {
            UpgradeOption[choice].apply(*context.player);  // 应用升级效果
            stack.changeState(std::make_unique<PlayingState>(window, stack, context));
            //UpgradeOption.clear();
        }
    }
}

void UpgradingState::update(sf::Time delta)
{

}

void UpgradingState::render()
{
    window.draw(overlay);
    window.draw(title);
    for (const auto& text : optionTexts) 
    {
        window.draw(text);
    }
}
