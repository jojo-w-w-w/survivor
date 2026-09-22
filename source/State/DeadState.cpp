#include <SFML/Graphics.hpp>
#include <iostream>
#include "DeadState.hpp"
#include "MenuState.hpp"
#include "Player.hpp"
#include "EnemyBase.hpp"
#include "Bullet.hpp"
#include "ResourceManager.hpp"

DeadState::DeadState(sf::RenderWindow& window, StateStack& stack, GameContext& context) :
window(window), stack(stack), context(context),
DeadBgSprite(DeadBgTexture),
font(ResourceManager::getFont("LiberationSans-Bold.ttf")),
titleText(*font), reStartText(*font), QuitToMenuText(*font)
{
    //添加死亡背景图
    if(!DeadBgTexture.loadFromFile("assets/DeadBackground.png"))
    {
        std::cerr << "Failed to load DeadBackground texture!" << std::endl;
    }

    //重新绑定图片资源
    DeadBgSprite.setTexture(DeadBgTexture, true);

    const sf::FloatRect bgBounds = DeadBgSprite.getLocalBounds();

    DeadBgSprite.setScale
    ({
        static_cast<float>(window.getSize().x) / bgBounds.size.x,
        static_cast<float>(window.getSize().y) / bgBounds.size.y
    });

    //标题
    titleText.setString("You Died !!!");
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

    //重新开始游戏按钮
    restartButton.setSize(sf::Vector2f(300.f, 80.f));
    
    const sf::Vector2f ReStartbuttonSize = restartButton.getSize();

    restartButton.setOrigin
    ({
        ReStartbuttonSize.x / 2.f,
        ReStartbuttonSize.y / 2.f
    });

    restartButton.setFillColor(sf::Color(100, 100, 100));

    restartButton.setPosition
    ({
        context.getScreenCenter().x,
        context.getScreenCenter().y * 0.80f
    });   //居中

    //重新开始文本设置
    reStartText.setString("reStart");
    reStartText.setCharacterSize(60);
    reStartText.setFillColor(sf::Color::White);
    //自动使文本居中
    sf::FloatRect reStartTextBounds = reStartText.getLocalBounds();
    reStartText.setOrigin
    ({
        reStartTextBounds.position.x + reStartTextBounds.size.x / 2, 
        reStartTextBounds.position.y + reStartTextBounds.size.y / 2
    });
    reStartText.setPosition({restartButton.getPosition()});

    //退出至菜单游戏按钮
    QuitToMenuButton.setSize(sf::Vector2f(300.f, 80.f));

    const sf::Vector2f QuitToMenubuttonSize = QuitToMenuButton.getSize();

    QuitToMenuButton.setOrigin
    ({
        QuitToMenubuttonSize.x / 2.f,
        QuitToMenubuttonSize.y / 2.f
    });

    QuitToMenuButton.setFillColor(sf::Color(100, 100, 100));
    QuitToMenuButton.setPosition
    ({
        context.getScreenCenter().x,
        context.getScreenCenter().y * 1.2f
    });   //居中
    //退出至菜单文本设置
    QuitToMenuText.setString("QuitToMenu");
    QuitToMenuText.setCharacterSize(60);
    QuitToMenuText.setFillColor(sf::Color::White);
    //自动使文本居中
    sf::FloatRect QuitToMenuTextBounds = QuitToMenuText.getLocalBounds();
    QuitToMenuText.setOrigin
    ({
        QuitToMenuTextBounds.position.x + QuitToMenuTextBounds.size.x / 2, 
        QuitToMenuTextBounds.position.y + QuitToMenuTextBounds.size.y / 2
    });
    QuitToMenuText.setPosition({QuitToMenuButton.getPosition()});
}

DeadState::~DeadState() = default;

void DeadState::handleInput(const sf::Event& event)
{
     //死亡界面按钮检测
    if(const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        //如果鼠标按下左键
        if(mousePressed->button == sf::Mouse::Button::Left)
        {
            //定义鼠标位置
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePressed->position);
            //当点击 reStart 时切换状态至重新游玩
            if(restartButton.getGlobalBounds().contains(mousePos))
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
            //当点击 QuitToMenu 时直接关闭窗口
            if(QuitToMenuButton.getGlobalBounds().contains(mousePos))
            {
               stack.changeState(std::make_unique<MenuState>(window, stack, context));
            }
        }
    }
}

void DeadState::update(sf::Time)
{

}

void DeadState::render()
{
    window.draw(DeadBgSprite);

    window.draw(titleText);

    window.draw(restartButton);
    window.draw(reStartText);

    window.draw(QuitToMenuButton);
    window.draw(QuitToMenuText);
}
