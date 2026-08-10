#include "EnemyFactory.hpp"
#include "Enemy.hpp"      // 你的普通敌人
#include "FastEnemy.hpp"
#include "Boss.hpp"
#include <random>
#include <array>


std::unique_ptr<EnemyBase> EnemyFactory::create(EnemyType type) 
{
    switch (type) 
    {
        case EnemyType::Normal: return std::make_unique<Enemy>();
        case EnemyType::Fast:   return std::make_unique<FastEnemy>();
        case EnemyType::Boss:   return std::make_unique<Boss>();
        default:                return nullptr;
    }
}

std::unique_ptr<EnemyBase> EnemyFactory::creatRandom()
{
    // 所有可用敌人类型的列表
    static const std::array<EnemyType, 3> allTypes = 
    {
        EnemyType::Normal,
        EnemyType::Fast,
        EnemyType::Boss
    };
    //当增加新敌人时，需要手动更新这个数组的大小和内容
    // 使用现代随机数引擎（替代 rand）
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<size_t> dist(0, allTypes.size() - 1);
    return create(allTypes[dist(gen)]);
}