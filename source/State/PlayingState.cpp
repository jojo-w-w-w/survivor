#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayingState.hpp"
#include "EnemyFactory.hpp"
#include "UpgradingState.hpp"

PlayingState::PlayingState(sf::RenderWindow& window, StateStack& stack, GameContext& context) :
window(window), stack(stack), context(context), PlayingBgSprite(PlayingBgTexture), hpText(font), expText(font), levelText(font)
{
    //绘制背景图
    if(!PlayingBgTexture.loadFromFile("assets/background.png"))
    {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    
    const sf::FloatRect bgBounds = PlayingBgSprite.getLocalBounds();

    PlayingBgSprite.setScale
    ({
        static_cast<float>(window.getSize().x) / bgBounds.size.x,
        static_cast<float>(window.getSize().y) / bgBounds.size.y
    });

    //血量文本
    hpText.setString("HP: 3/3");
    hpText.setCharacterSize(20);
    hpText.setFillColor(sf::Color::White);
    hpText.setPosition({230.f, 18.f});
    //血量条背景
    hpBarBg.setSize(sf::Vector2f(200.f, 20.f));
    hpBarBg.setFillColor(sf::Color(60, 60, 60));
    hpBarBg.setPosition({20.f, 20.f});
    //血量条
    hpBar.setSize(sf::Vector2f(200.f, 20.f));
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setPosition({20.f, 20.f});
    //经验文本
    expText.setString("EXP: 0/10");
    expText.setCharacterSize(18);
    expText.setFillColor(sf::Color::White);
    expText.setPosition({230.f, 48.f});
    //经验条背景
    expBarBg.setSize(sf::Vector2f(200.f, 15.f));
    expBarBg.setFillColor(sf::Color(60, 60, 60));
    expBarBg.setPosition({20.f, 50.f});
    //经验条
    expBar.setSize(sf::Vector2f(200.f, 15.f));
    expBar.setFillColor(sf::Color::Green);
    expBar.setPosition({20.f, 50.f});
    //下一级文本
    levelText.setString("Level : 1");
    levelText.setCharacterSize(222);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition({20.f, 75.f});
    
    //生成敌人
    context.enemies.clear();
    context.enemies.push_back(EnemyFactory::creatRandom());
}

PlayingState::~PlayingState() = default;

void PlayingState::handleInput(const sf::Event& event)
{
    if(const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        //按下 ESC 切换至暂停状态
        if(keyPressed->code == sf::Keyboard::Key::Escape)
        {
            stack.changeState(std::make_unique<PauseState>(window, stack, context));
        }
    }
   

}

void PlayingState::update(sf::Time delta)
{
    //处理玩家移动
    float dt = delta.asSeconds();
    sf::Vector2f direction(0.f, 0.f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        direction.y -= 1.f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        direction.x -= 1.f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        direction.y += 1.f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        direction.x += 1.f;
    
    if(context.player)
    {
        context.player->move(direction, dt);
    }

    //敌人移动
    for(auto& enemy : context.enemies)
    {
        enemy->update(dt, *context.player);
    }

    //子弹移动


    //碰撞检测:
    //敌人与子弹的碰撞检测
    for(auto& enemy : context.enemies)
    {
        //如果敌人已经死亡就遍历下一个敌人
        if(!enemy->isActive())
            continue;

        //如果子弹与敌人发生碰撞
        for(auto& bullet : context.bullets)
        {
            //当前子弹不存在则遍历下一个
            if(!bullet->isActive())
                continue;
            
            //如果子弹的边框与敌人的边框相交
            if(bullet->getBound().findIntersection(enemy->getBound()).has_value())
            {
                bullet->deActive();//子弹消失
                enemy->deActive();//敌人消失
                context.player->addExp(enemy->getExp());//敌人死亡玩家获得经验
                break;
            }
        }
    }
    //敌人与玩家的碰撞检测
    for(auto& enemy : context.enemies)
    {
        if(!enemy->isActive())
            continue;
        
        //如果玩家与敌人发生碰撞
        if(context.player->getBound().findIntersection(enemy->getBound()).has_value())
        {
            enemy->deActive();//敌人消失
            context.player->isDamage(1);//玩家受到伤害
            context.player->addExp(enemy->getExp());//敌人死亡玩家获得经验
        }

        //如果玩家死亡，则游戏结束
        if(context.player->isDead())
        {
            //切换至死亡界面

            //输出死亡文本
            std::cout << "You Died!" << std::endl;
            window.close();
        }
    }

    //如果经验条满了，切换至更新状态
    if(context.player->justLevelUp())
    {
        stack.changeState(std::make_unique<UpgradingState>(window, stack, context));
    }

    //更新HUD
    if(context.player)
    {
        // 更新血条
        float hpPercent = static_cast<float>(context.player->getHP()) / context.player->getMaxHp();
        if (hpPercent < 0.f) hpPercent = 0.f;
        hpBar.setSize(sf::Vector2f(200.f * hpPercent, 20.f));

        // 更新血条文字
        hpText.setString("HP: " + std::to_string(context.player->getHP()) + "/" + std::to_string(context.player->getMaxHp()));

        // 更新经验条
        float expPercent = static_cast<float>(context.player->getExp()) / context.player->getExpToNext();
        expBar.setSize(sf::Vector2f(200.f * expPercent, 15.f));

        // 更新经验文字
        expText.setString("EXP: " + std::to_string(context.player->getExp()) + "/" + std::to_string(context.player->getExpToNext()));

        // 更新等级文字
        levelText.setString("Level: " + std::to_string(context.player->getLevel()));
    }
}

void PlayingState::render()
{
    //绘制背景
    window.draw(PlayingBgSprite);

    //只有在游戏进程发生时才绘制 HDU
    window.draw(hpText);
    window.draw(hpBarBg);
    window.draw(hpBar);
    window.draw(expText);
    window.draw(expBarBg);
    window.draw(expBar);
    window.draw(levelText);

    //绘制玩家
    if(context.player)
    {
        context.player->render(window);
    }

    //绘制子弹
    for(auto& bullet : context.bullets)
    {
        if(bullet->isActive())
            bullet->render(window);
    }

    //绘制敌人
    for(auto& enemy : context.enemies)
    {
        //当敌人存活时才绘制敌人
        if(enemy->isActive())
            enemy->render(window);
    }
}