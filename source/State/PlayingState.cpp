#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
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
    
    //重新绑定图片资源
    PlayingBgSprite.setTexture(PlayingBgTexture, true);

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

    //子弹发射逻辑
    //如果玩家此时可以发射子弹
    if(context.player->canshoot(dt))
    {
        //遍历所有活着的敌人找到最近的
        const EnemyBase* nearstEnemy = nullptr;
        float minDistance = std::numeric_limits<float>::max();//将最小距离初始化为极大值方便更新
        for(const auto& enemy : context.enemies)
        {
            //如果敌人死亡就跳过
            if(!enemy->isActive())
                continue;

            //获得该敌人与玩家之间的坐标差，为了下面计算该敌人与玩家之间的距离
            sf::Vector2f diff = enemy->getPosition() - context.player->getPosition();

            //计算该敌人与玩家之间的距离
            float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

            //更新最小距离
            if(dist < minDistance)
            {
                minDistance = dist;
                nearstEnemy = enemy.get();//更新最近敌人指针
            }
        }
        //  && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)
        //如果找到敌人并按下 J 就发射子弹
        if(nearstEnemy != nullptr)
        {
            sf::Vector2f direction = nearstEnemy->getPosition() - context.player->getPosition();
            float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if(len > 0)
                direction /= len;//归一化

            // 基础方向角度
            float baseAngle = std::atan2(direction.y, direction.x);

            float spread = 0.15f;  // 散射弧度，约 8.6 度

            int bulletCount = context.player->getBulletCount();   // 需要添加这个公有方法
            for (int i = 0; i < bulletCount; ++i) 
            {
                float angle = baseAngle;
                if (bulletCount > 1) 
                {
                    float offset = spread * (i - (bulletCount - 1.0f) / 2.0f);
                    angle += offset;
                }
            
                sf::Vector2f bulletDir(std::cos(angle), std::sin(angle));

                context.bullets.push_back(std::make_unique<Bullet>());                                 //向子弹数组里添加子弹
                context.bullets.back()->launch(context.player->getPosition(), bulletDir, context.player->getBulletSpeed()); //将子弹的状态设为激活
            }
            
        }
    }

    //更新所有子弹的状态
    for (auto& bullet : context.bullets)
    {
        if (bullet->isActive())
        {
            bullet->update(dt);
        }
    }

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