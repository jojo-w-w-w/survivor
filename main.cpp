#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>
#include <cstdlib>
#include "Player.hpp"
#include "EnemyBase.hpp"
#include "Enemy.hpp"
#include "EnemyFactory.hpp"
#include "Bullet.hpp"
#include "Upgrade.hpp"

enum class Gamestate
{
    Menu,
    Playing,
    Upgrading    
};

int main() 
{
    Gamestate gamestate = Gamestate::Menu;//设置游戏初始状态为游玩

    sf::RenderWindow window(sf::VideoMode(1280,720), "Roguelike Survivor");//设置游戏窗口

    if (!window.isOpen()) //如果窗口打开失败
    {
        std::cerr << "Failed to create window" << std::endl;
        return 1;
    }

    window.setFramerateLimit(60);               //设置帧率为60

    //设置开始界面背景图片
    sf::Texture StartBgTexture;
    sf::Sprite StartBgSprite;
    if(!StartBgTexture.loadFromFile("assets/StartBackground.png"))
    {
        std::cerr << "Failed to load StartBackground texture!" << std::endl;
    }
    StartBgSprite.setTexture(StartBgTexture);

    StartBgSprite.setScale
    (
        window.getSize().x / StartBgSprite.getLocalBounds().width,
        window.getSize().y / StartBgSprite.getLocalBounds().height
    );

    //设置游戏进程背景图片
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    if(!bgTexture.loadFromFile("assets/background.png"))
    {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    bgSprite.setTexture(bgTexture);

    bgSprite.setScale
    (
        window.getSize().x / bgSprite.getLocalBounds().width,
        window.getSize().y / bgSprite.getLocalBounds().height
    );

    sf::Clock clock;

    //菜单 UI
    sf::Font font_Menu;

    font_Menu.loadFromFile("LiberationSans-Bold.ttf");

    sf::Text titleText("ROGUELIKE SURVIVOR", font_Menu, 60);

    titleText.setFillColor(sf::Color::White);

    titleText.setPosition(200.f, 150.f);

    // 按钮矩形
    sf::RectangleShape startButton(sf::Vector2f(300.f, 80.f));

    startButton.setFillColor(sf::Color(100, 100, 100));

    startButton.setPosition(490.f, 350.f);  // 居中

    sf::Text buttonText("Start Game", font_Menu, 40);

    buttonText.setFillColor(sf::Color::White);

    buttonText.setPosition(510.f, 360.f);  // 稍微调整使文字在按钮内居中

    //HUD
    sf::Font font_HUD;

    sf::RectangleShape hpBarBg(sf::Vector2f(200.f, 20.f));
    hpBarBg.setFillColor(sf::Color(60, 60, 60));
    hpBarBg.setPosition(20.f, 20.f);

    sf::RectangleShape hpBar(sf::Vector2f(200.f, 20.f));
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setPosition(20.f, 20.f);

    sf::RectangleShape expBarBg(sf::Vector2f(200.f, 15.f));
    expBarBg.setFillColor(sf::Color(60, 60, 60));
    expBarBg.setPosition(20.f, 50.f);

    sf::RectangleShape expBar(sf::Vector2f(200.f, 15.f));
    expBar.setFillColor(sf::Color::Green);
    expBar.setPosition(20.f, 50.f);

    sf::Text hpText("HP: 3/3", font_HUD, 20);
    hpText.setFillColor(sf::Color::White);
    hpText.setPosition(230.f, 18.f);

    sf::Text expText("EXP: 0/10", font_HUD, 18);
    expText.setFillColor(sf::Color::White);
    expText.setPosition(230.f, 48.f);

    sf::Text levelText("Level: 1", font_HUD, 22);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(20.f, 75.f);

    Player player;                              //先创建一个玩家对象
    
    //创建敌人容器
    std::vector<std::unique_ptr<EnemyBase>> enemies;
    float spawnTimer = 0.f;                     //生成敌人的时间
    const float spawnInterval = 2.f;            //每两秒生成一个敌人

    //创建子弹容器
    std::vector<std::unique_ptr<Bullet>> bullets;

    //创建字体和升级选项容器
    sf::Font font_Upgrade;
    if (!font_Upgrade.loadFromFile("LiberationSans-Bold.ttf")) 
    {
        std::cerr << "Font load failed!" << std::endl;
        return -1;
    }

    std::vector<Upgrade> currentChoices;   // 本次升级的 3 个选项

    while (window.isOpen())//渲染事件
    {
	    sf::Time dt = clock.restart();
	    float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // 菜单状态下检测鼠标点击
            if (gamestate == Gamestate::Menu && event.type == sf::Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (startButton.getGlobalBounds().contains(mousePos)) 
                    {
                        // 切换到游戏状态，并重置游戏数据
                        gamestate = Gamestate::Playing;
                        player.reset();
                        enemies.clear();
                        bullets.clear();
                        spawnTimer = 0.f;
                    }
                }
            }
            
            //如果当前的游戏状态为更新
            if(gamestate == Gamestate::Upgrading)
            {
                if(event.type == sf::Event::KeyPressed)
                {
                    int choice = -1;

                    if (event.key.code == sf::Keyboard::Num1) 
                        choice = 0;

                    else if (event.key.code == sf::Keyboard::Num2) 
                        choice = 1;

                    else if (event.key.code == sf::Keyboard::Num3) 
                        choice = 2;

                    if (choice >= 0 && choice < currentChoices.size()) 
                    {
                        currentChoices[choice].apply(player);  // 应用升级效果
                        gamestate = Gamestate::Playing;
                        currentChoices.clear();
                    }
                }
            }
        }

        //如果当前的游戏状态为游玩
        if(gamestate == Gamestate::Playing)
        {
            

            player.update(deltaTime);//更新玩家状态

            //如果玩家此时可以发射子弹
            if(player.canshoot(deltaTime))
            {
                //遍历所有活着的敌人找到最近的
                const EnemyBase* nearstEnemy = nullptr;
                float minDistance = std::numeric_limits<float>::max();//将最小距离初始化为极大值方便更新
                for(const auto& enemy : enemies)
                {
                    //如果敌人死亡就跳过
                    if(!enemy->isActive())
                        continue;

                    //获得该敌人与玩家之间的坐标差，为了下面计算该敌人与玩家之间的距离
                    sf::Vector2f diff = enemy->getPosition() - player.getPosition();

                    //计算该敌人与玩家之间的距离
                    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

                    //更新最小距离
                    if(dist < minDistance)
                    {
                        minDistance = dist;
                        nearstEnemy = enemy.get();//更新最近敌人指针
                    }
                }

                //如果找到敌人就发射子弹
                if(nearstEnemy != nullptr)
                {
                    sf::Vector2f direction = nearstEnemy->getPosition() - player.getPosition();
                    float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);

                    if(len > 0)
                        direction /= len;//归一化

                     // 基础方向角度
                    float baseAngle = std::atan2(direction.y, direction.x);

                    float spread = 0.15f;  // 散射弧度，约 8.6 度

                    int bulletCount = player.getBulletCount();   // 需要添加这个公有方法
                    for (int i = 0; i < bulletCount; ++i) 
                    {
                        float angle = baseAngle;
                        if (bulletCount > 1) 
                        {
                            float offset = spread * (i - (bulletCount - 1.0f) / 2.0f);
                            angle += offset;
                        }
                    
                        sf::Vector2f bulletDir(std::cos(angle), std::sin(angle));

                        bullets.push_back(std::make_unique<Bullet>());                                 //向子弹数组里添加子弹
                        bullets.back()->launch(player.getPosition(), bulletDir, player.getBulletSpeed()); //将子弹的状态设为激活
                    }
                }
            }

            //敌人生成
            spawnTimer += deltaTime;
            if(spawnTimer >= spawnInterval)
            {
                spawnTimer = 0.f;
                enemies.push_back(EnemyFactory::creatRandom());
            }

            //更新所有敌人
            for(auto& enemy : enemies)
            {
                enemy->update(deltaTime, player.getPosition());
            }

            //更新所有子弹
            for(auto& bullet : bullets)
            {
                if(bullet->isActive())
                {
                    bullet->update(deltaTime);
                }
            }

            //敌人与子弹的碰撞检测
            for(auto& enemy : enemies)
            {
                //如果敌人已经死亡就遍历下一个敌人
                if(!enemy->isActive())
                    continue;

                //如果子弹与敌人发生碰撞
                for(auto& bullet : bullets)
                {
                    //当前子弹不存在则遍历下一个
                    if(!bullet->isActive())
                        continue;
                    
                    //如果子弹的边框与敌人的边框相交
                    if(bullet->getBound().intersects(enemy->getBound()))
                    {
                        bullet->deActive();//子弹消失
                        enemy->deActive();//敌人消失
                        player.addExp(enemy->getExp());//敌人死亡玩家获得经验
                        break;
                    }
                }
            }
            
            //敌人与玩家的碰撞检测
            for(auto& enemy : enemies)
            {
                if(!enemy->isActive())
                    continue;
                
                //如果玩家与敌人发生碰撞
                if(player.getBound().intersects(enemy->getBound()))
                {
                    enemy->deActive();//敌人消失
                    player.isDamage(1);//玩家受到伤害
                    player.addExp(enemy->getExp());//敌人死亡玩家获得经验
                }

                //如果玩家死亡，则游戏结束
                if(player.isDead())
                {
                    std::cout << "You Died!" << std::endl;
                    window.close();
                }
            }
                            
            //清理失效的子弹
            bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const std::unique_ptr<Bullet>&b)
            {
                return !b->isActive();
            }), bullets.end());

            //检查升级
            if(player.justLevelUp())
            {
                gamestate = Gamestate::Upgrading;

                //随机抽取三个升级选项
                currentChoices.clear();
                auto pool = allUpgrades;
                std::random_device rd;
                std::mt19937 g(rd());
                std::shuffle(pool.begin(), pool.end(), g);
                for (int i = 0; i < 3 && i < pool.size(); ++i)
                {
                    currentChoices.push_back(pool[i]);
                }
            }

        }
  
        // 更新血条
        float hpPercent = static_cast<float>(player.getHP()) / player.getMaxHp();
        if (hpPercent < 0.f) hpPercent = 0.f;
        hpBar.setSize(sf::Vector2f(200.f * hpPercent, 20.f));

        // 更新血条文字
        hpText.setString("HP: " + std::to_string(player.getHP()) + "/" + std::to_string(player.getMaxHp()));

        // 更新经验条
        float expPercent = static_cast<float>(player.getExp()) / player.getExpToNext();
        expBar.setSize(sf::Vector2f(200.f * expPercent, 15.f));

        // 更新经验文字
        expText.setString("EXP: " + std::to_string(player.getExp()) + "/" + std::to_string(player.getExpToNext()));

        // 更新等级文字
        levelText.setString("Level: " + std::to_string(player.getLevel()));

        window.clear(sf::Color::Black);

        if (gamestate == Gamestate::Menu) 
        {
            //绘制开始游戏背景图
            window.draw(StartBgSprite);

            // 绘制菜单
            window.draw(titleText);
            window.draw(startButton);
            window.draw(buttonText);
        }

        if(gamestate == Gamestate::Playing)
        {
            //绘制背景
            window.draw(bgSprite);

            //只有在游戏进程发生时才绘制 HDU
            window.draw(hpBarBg);
            window.draw(hpBar);
            window.draw(hpText);
            window.draw(expBarBg);
            window.draw(expBar);
            window.draw(expText);
            window.draw(levelText);

            //绘制玩家
            player.render(window);

            //绘制子弹
            for(auto& bullet : bullets)
            {
                if(bullet->isActive())
                    bullet->render(window);
            }

            //绘制敌人
            for(auto& enemy : enemies)
            {
                //当敌人存活时才绘制敌人
                if(enemy->isActive())
                    enemy->render(window);
            }
        }
        
        if(gamestate == Gamestate::Upgrading)
        {
            // 半透明黑色遮罩
            sf::RectangleShape overlay(sf::Vector2f(1280, 720));
            overlay.setFillColor(sf::Color(0, 0, 0, 180)); // 180 是透明度
            window.draw(overlay);

            // 绘制标题
            sf::Text title("LEVEL UP!", font_Upgrade, 50);
            title.setFillColor(sf::Color::White);
            title.setPosition(400.f, 100.f);
            window.draw(title);

            // 绘制三个选项
            for (size_t i = 0; i < currentChoices.size(); ++i) 
            {
                sf::Text option;
                option.setFont(font_Menu);
                option.setString(std::to_string(i+1) + ". " + currentChoices[i].name + "\n   " + currentChoices[i].description);
                option.setCharacterSize(30);
                option.setFillColor(sf::Color::White);
                option.setPosition(200.f, 250.f + i * 120.f);
                window.draw(option);
            }
        }

        window.display();
    }

    std::cout << "Game Over!" << std::endl;
    return 0;
}
