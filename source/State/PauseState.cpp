#include <SFML/Graphics.hpp>
#include <iostream>
#include "PauseState.hpp"
#include "MenuState.hpp"
#include "ResourceManager.hpp"

PauseState::PauseState(sf::RenderWindow& window, StateStack& stack, GameContext& context) :
window(window), stack(stack), context(context), 
PauseBgSprite(PauseBgTexture), 
font(ResourceManager::getFont("LiberationSans-Bold.ttf")),
titleText(*font), ContinueText(*font), QuitText(*font)
{
    //绘制暂停背景图
    if(!PauseBgTexture.loadFromFile("assets/PauseBackground.png"))
    {
        std::cerr << "Failed to load PauseBackground texture!" << std::endl;
    }

    //重新绑定图片资源
    PauseBgSprite.setTexture(PauseBgTexture, true);

    const sf::FloatRect bgBounds = PauseBgSprite.getLocalBounds();

    PauseBgSprite.setScale
    ({
        static_cast<float>(window.getSize().x) / bgBounds.size.x,
        static_cast<float>(window.getSize().y) / bgBounds.size.y
    });

    //标题
    titleText.setString("PAUSED");
    titleText.setCharacterSize(120);
    titleText.setFillColor(sf::Color::White);

    const sf::FloatRect titleBounds = titleText.getLocalBounds();

    titleText.setOrigin
    ({
        titleBounds.position.x + titleBounds.size.x / 2.f,
        titleBounds.position.y + titleBounds.size.y / 2.f
    });

    titleText.setPosition
    ({
        context.getScreenCenter().x,
        context.getScreenCenter().y * 0.25f
    });

    //继续游戏按钮
    ContinueButton.setSize(sf::Vector2f({300.f, 80.f}));

    const sf::Vector2f ContinuebuttonSize = ContinueButton.getSize();

    ContinueButton.setOrigin
    ({
        ContinuebuttonSize.x / 2.f,
        ContinuebuttonSize.y / 2.f
    });

    ContinueButton.setFillColor(sf::Color(100, 100, 100));

    ContinueButton.setPosition
    ({
        context.getScreenCenter().x,
        context.getScreenCenter().y * 0.80f
    });   //居中

    //继续游戏文本设置
    ContinueText.setString("Continue");
    ContinueText.setCharacterSize(40);
    ContinueText.setFillColor(sf::Color::White);
    //自动使文本居中
    sf::FloatRect ContinueTextBounds = ContinueText.getLocalBounds();
    ContinueText.setOrigin
    ({
        ContinueTextBounds.position.x + ContinueTextBounds.size.x / 2.f, 
        ContinueTextBounds.position.y + ContinueTextBounds.size.y / 2.f
    });
    ContinueText.setPosition({ContinueButton.getPosition()});

    //退出游戏按钮
    QuitButton.setSize(sf::Vector2f({300.f, 80.f}));

    const sf::Vector2f QuitbuttonSize = QuitButton.getSize();

    QuitButton.setOrigin
    ({
        QuitbuttonSize.x / 2.f,
        QuitbuttonSize.y / 2.f
    });

    QuitButton.setFillColor(sf::Color(100, 100, 100));

    QuitButton.setPosition
    ({
        context.getScreenCenter().x,
        context.getScreenCenter().y * 1.2f
    });   //居中
    //退出文本设置
    QuitText.setString("Quit");
    QuitText.setCharacterSize(60);
    QuitText.setFillColor(sf::Color::White);
    //自动使文本居中
    sf::FloatRect QuitTextBounds = QuitText.getLocalBounds();
    QuitText.setOrigin
    ({
        QuitTextBounds.position.x + QuitTextBounds.size.x / 2.f, 
        QuitTextBounds.position.y + QuitTextBounds.size.y / 2.f
    });
    QuitText.setPosition({QuitButton.getPosition()});
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
    window.draw(PauseBgSprite);

    window.draw(titleText);

    window.draw(ContinueButton);
    window.draw(ContinueText);

    window.draw(QuitButton);
    window.draw(QuitText);
}
