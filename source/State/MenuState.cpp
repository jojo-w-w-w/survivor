#include <SFML/Graphics.hpp>
#include <iostream>
#include "MenuState.hpp"

MenuState::MenuState(sf::RenderWindow& window, StateStack& stack, GameContext& context) : 
window(window), stack(stack), context(context), MenuBgSprite(MenuBgTexture), titleText(font), StartText(font), QuitText(font)
{
    //绘制背景图
    if(!MenuBgTexture.loadFromFile("assets/StartBackground.png"))
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

    //加载文字包
    if(!font.openFromFile("LiberationSans-Bold.ttf"))
    {
        std::cerr << "Failed to load font\n";
    }    
    //标题
    titleText.setString("RougeLike");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({480.f, 150.f});

    //开始游戏按钮
    startButton.setSize(sf::Vector2f(300.f, 80.f));
    startButton.setFillColor(sf::Color(100, 100, 100));
    startButton.setPosition({490.f, 300.f});   //居中
    //开始文本设置
    StartText.setString("Start");
    StartText.setCharacterSize(60);
    StartText.setFillColor(sf::Color::White);
    //自动使文本居中
    sf::FloatRect StartTextBounds = StartText.getLocalBounds();
    StartText.setOrigin({StartTextBounds.position.x + StartTextBounds.size.x / 2, StartTextBounds.position.y + StartTextBounds.size.y / 2});
    StartText.setPosition({startButton.getPosition().x + startButton.getSize().x / 2, startButton.getPosition().y + startButton.getSize().y / 2});

    //退出游戏按钮
    QuitButton.setSize(sf::Vector2f(300.f, 80.f));
    QuitButton.setFillColor(sf::Color(100, 100, 100));
    QuitButton.setPosition({490.f, 450.f});   //居中
    //退出文本设置
    QuitText.setString("Quit");
    QuitText.setCharacterSize(60);
    QuitText.setFillColor(sf::Color::White);
    //自动使文本居中
    sf::FloatRect QuitTextBounds = QuitText.getLocalBounds();
    QuitText.setOrigin({QuitTextBounds.position.x + QuitTextBounds.size.x / 2, QuitTextBounds.position.y + QuitTextBounds.size.y / 2});
    QuitText.setPosition({QuitButton.getPosition().x + QuitButton.getSize().x / 2, QuitButton.getPosition().y + QuitButton.getSize().y / 2});
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
                context.player = std::make_unique<Player>();
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