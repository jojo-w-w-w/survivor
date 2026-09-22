#include <SFML/Graphics.hpp>
#include <iostream>
#include "MenuState.hpp"
#include "Player.hpp"
#include "EnemyBase.hpp"
#include "Bullet.hpp"
#include "ResourceManager.hpp"

MenuState::MenuState(sf::RenderWindow& window, StateStack& stack, GameContext& context) :
window(window), stack(stack), context(context), MenuBgSprite(MenuBgTexture),
font(ResourceManager::getFont("LiberationSans-Bold.ttf")),
titleText(*font), StartText(*font), QuitText(*font)
{
    //绘制背景图
    if(!MenuBgTexture.loadFromFile("assets/MenuBackground.png"))
    {
        std::cerr << "Failed to load StartBackground texture!" << std::endl;
    }

    //重新绑定图片资源
    MenuBgSprite.setTexture(MenuBgTexture, true);

    const sf::FloatRect bgBounds = MenuBgSprite.getLocalBounds();

    MenuBgSprite.setScale
    ({
        static_cast<float>(window.getSize().x) / bgBounds.size.x,
        static_cast<float>(window.getSize().y) / bgBounds.size.y
    });

    //标题
    titleText.setString("RogueLike");
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

    //开始游戏按钮
    startButton.setSize(sf::Vector2f(300.f, 80.f));

    const sf::Vector2f StartbuttonSize = startButton.getSize();

    startButton.setOrigin
    ({
        StartbuttonSize.x / 2.f,
        StartbuttonSize.y / 2.f
    });

    startButton.setFillColor(sf::Color(100, 100, 100));

    startButton.setPosition
    ({
        context.getScreenCenter().x,
        context.getScreenCenter().y * 0.80f
    });   //居中

    //开始文本设置
    StartText.setString("Start");
    StartText.setCharacterSize(60);
    StartText.setFillColor(sf::Color::White);
    //自动使文本居中
    sf::FloatRect StartTextBounds = StartText.getLocalBounds();
    StartText.setOrigin
    ({
        StartTextBounds.position.x + StartTextBounds.size.x / 2.f, 
        StartTextBounds.position.y + StartTextBounds.size.y / 2.f
    });
    StartText.setPosition({startButton.getPosition()});

    //退出游戏按钮
    QuitButton.setSize(sf::Vector2f(300.f, 80.f));

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

MenuState::~MenuState() = default;

void MenuState::handleInput(const sf::Event& event)
{
    //菜单界面按钮检测
    if(const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        //如果鼠标按下左键
        if(mousePressed->button == sf::Mouse::Button::Left)
        {
            //定义鼠标位置
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePressed->position);
            //当点击 Start 时切换状态至游玩
            if(startButton.getGlobalBounds().contains(mousePos))
            {
                //游戏准备切换至游玩时创建玩家
                context.player = std::make_unique<Player>(context.getScreenCenter());
                //清除之前的敌人
                context.enemies.clear();
                //清除之前的子弹
                context.bullets.clear();
                //切换游戏状态
                stack.changeState(std::make_unique<PlayingState>(window, stack, context));
            }
            //当点击 Quit 时直接关闭窗口
            if(QuitButton.getGlobalBounds().contains(mousePos))
            {
               window.close();
            }
        }
    }
}

void MenuState::update(sf::Time)
{

}

void MenuState::render()
{
    window.draw(MenuBgSprite);

    window.draw(titleText);

    window.draw(startButton);
    window.draw(StartText);

    window.draw(QuitButton);
    window.draw(QuitText);
}