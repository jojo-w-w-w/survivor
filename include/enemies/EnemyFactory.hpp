#pragma once
#include <memory>
#include "EnemyBase.hpp"

class EnemyFactory 
{
public:
    enum class EnemyType 
    {
        Normal,
        Fast,
        Boss
    };
    
    static std::unique_ptr<EnemyBase> create(EnemyType type);

    static std::unique_ptr<EnemyBase> creatRandom();
};