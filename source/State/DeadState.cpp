#include <SFML/Graphics.hpp>
#include <iostream>
#include "DeadState.hpp"

DeadState::DeadState(sf::RenderWindow& window, StateStack& stack, GameContext& context) :
window(window), stack(stack), context(context), DeadBgSprite(DeadBgTexture), titleText(font), reStartText(font), QuitToMenuText(font) 
{
    //添加死亡背景图

    //加载文字包
    if(!font.openFromFile("LiberationSans-Bold.ttf"))
    {
        std::cerr << "Failed to load font\n";
    }    
    //标题
    titleText.setString("You Died !!!");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({480.f, 150.f});

    //重新开始游戏按钮
    restartButton.setSize(sf::Vector2f(300.f, 80.f));
    restartButton.setFillColor(sf::Color(100, 100, 100));
    restartButton.setPosition({490.f, 300.f});   //居中
    //重新开始文本设置
    reStartText.setString("reStart");
    reStartText.setCharacterSize(60);
    reStartText.setFillColor(sf::Color::White);
    //自动使文本居中
    sf::FloatRect reStartTextBounds = reStartText.getLocalBounds();
    reStartText.setOrigin({reStartTextBounds.position.x + reStartTextBounds.size.x / 2, reStartTextBounds.position.y + reStartTextBounds.size.y / 2});
    reStartText.setPosition({restartButton.getPosition().x + restartButton.getSize().x / 2, restartButton.getPosition().y + restartButton.getSize().y / 2});

    //退出至菜单游戏按钮
    QuitToMenuButton.setSize(sf::Vector2f(300.f, 80.f));
    QuitToMenuButton.setFillColor(sf::Color(100, 100, 100));
    QuitToMenuButton.setPosition({490.f, 450.f});   //居中
    //退出至菜单文本设置
    QuitToMenuText.setString("QuitToMenu");
    QuitToMenuText.setCharacterSize(60);
    QuitToMenuText.setFillColor(sf::Color::White);
    //自动使文本居中
    sf::FloatRect QuitToMenuTextBounds = QuitToMenuText.getLocalBounds();
    QuitToMenuText.setOrigin({QuitToMenuTextBounds.position.x + QuitToMenuTextBounds.size.x / 2, QuitToMenuTextBounds.position.y + QuitToMenuTextBounds.size.y / 2});
    QuitToMenuText.setPosition({QuitToMenuButton.getPosition().x + QuitToMenuButton.getSize().x / 2, QuitToMenuButton.getPosition().y + QuitToMenuButton.getSize().y / 2});
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
                context.player = std::make_unique<Player>();
                //清除之前的敌人
                context.enemies.clear();
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

void DeadState::update(sf::Time delta) 
{

}

void DeadState::render() 
{
    // window.draw(MenuBgSprite);

    window.draw(titleText);

    window.draw(restartButton);
    window.draw(reStartText);
    
    window.draw(QuitToMenuButton);
    window.draw(QuitToMenuText);
}
