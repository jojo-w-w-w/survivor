#include <SFML/Graphics.hpp>
#include <iostream>
#include "PauseState.hpp"

PauseState::PauseState(sf::RenderWindow& window, StateStack& stack, GameContext& context) :
window(window), stack(stack), context(context), titleText(font), ContinueText(font), QuitText(font)
{
    //绘制暂停背景图

    //加载文字包
    if(!font.openFromFile("LiberationSans-Bold.ttf"))
    {
        std::cerr << "Failed to load font\n";
    }    
    //标题
    titleText.setString("PAUSED");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({480.f, 100.f});

    //继续游戏按钮
    ContinueButton.setSize(sf::Vector2f({300.f, 80.f}));
    ContinueButton.setFillColor(sf::Color(100, 100, 100));
    ContinueButton.setPosition({490.f, 300.f});   //居中
    //继续游戏文本设置
    ContinueText.setString("Continue");
    ContinueText.setCharacterSize(40);
    ContinueText.setFillColor(sf::Color::White);
    //自动使文本居中
    sf::FloatRect ContinueTextBounds = ContinueText.getLocalBounds();
    ContinueText.setOrigin({ContinueTextBounds.position.x + ContinueTextBounds.size.x / 2.f, ContinueTextBounds.position.y + ContinueTextBounds.size.y / 2.f});
    ContinueText.setPosition({ContinueButton.getPosition().x + ContinueButton.getSize().x / 2.f, ContinueButton.getPosition().y + ContinueButton.getSize().y / 2.f});

    //退出游戏按钮
    QuitButton.setSize(sf::Vector2f({300.f, 80.f}));
    QuitButton.setFillColor(sf::Color(100, 100, 100));
    QuitButton.setPosition({490.f, 450.f});   //居中
    //退出文本设置
    QuitText.setString("Quit");
    QuitText.setCharacterSize(60);
    QuitText.setFillColor(sf::Color::White);
    //自动使文本居中
    sf::FloatRect QuitTextBounds = QuitText.getLocalBounds();
    QuitText.setOrigin({QuitTextBounds.position.x + QuitTextBounds.size.x / 2.f, QuitTextBounds.position.y + QuitTextBounds.size.y / 2.f});
    QuitText.setPosition({QuitButton.getPosition().x + QuitButton.getSize().x / 2.f, QuitButton.getPosition().y + QuitButton.getSize().y / 2.f});
}

PauseState::~PauseState() = default;

void PauseState::handleInput(const sf::Event& event)
{
    //暂停界面按钮检测
    if(const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        //如果鼠标按下左键
        if(mousePressed->button == sf::Mouse::Button::Left)
        {
            //定义鼠标位置
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePressed->position);
            //当点击 Continue 时切换状态至游玩
            if(ContinueButton.getGlobalBounds().contains(mousePos))
            {
                //切换至游戏状态
                stack.popState();
            }
            //当点击 Quit 时退出至菜单界面
            if(QuitButton.getGlobalBounds().contains(mousePos))
            {
               stack.changeState(std::make_unique<MenuState>(window, stack, context));
            }
        }
    }
}

void PauseState::update(sf::Time)
{

}

void PauseState::render()
{
    //绘制背景
    //window.draw(MenuBgSprite);

    window.draw(titleText);

    window.draw(ContinueButton);
    window.draw(ContinueText);
    
    window.draw(QuitButton);
    window.draw(QuitText);
}
