#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "StateStack.hpp"
#include "GameContext.hpp"

struct GameContext;

class PlayingState : public GameState
{
public:
    PlayingState(sf::RenderWindow& window, StateStack& stack, GameContext& context);
    ~PlayingState() override;

    //生成敌人
    void spawnEnemy();

    void handleInput(const sf::Event& event) override;
    void update(sf::Time delta) override;
    void render() override;

private:
    sf::RenderWindow& window;
    StateStack& stack;
    GameContext& context;

    //设置游玩界面背景图片
    sf::Texture PlayingBgTexture;
    sf::Sprite PlayingBgSprite;

    //设置游玩界面的 HUD
    sf::Font font;
    //血量
    sf::Text hpText;
    sf::RectangleShape hpBarBg;
    sf::RectangleShape hpBar;
    //经验
    sf::Text expText;
    sf::RectangleShape expBarBg;
    sf::RectangleShape expBar;

    sf::Text levelText;
    
    //游玩时的敌人生成
    float enemySpawnTimer{0.f};
    float enemySpawnInterval{1.f};//每秒生成一只
};