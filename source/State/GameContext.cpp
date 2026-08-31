#include <SFML/Graphics.hpp>
#include "GameContext.hpp"

GameContext::GameContext() : player(std::make_unique<Player>()), textureManager(std::make_unique<ResourceManager>()) 
{
    // 初始时怪物列表为空，进入战斗状态后再生成

}