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
    
    static std::unique_ptr<EnemyBase> create(EnemyType type, sf::Vector2f startPosition);

    static std::unique_ptr<EnemyBase> createRandom(sf::Vector2f startPosition);
};