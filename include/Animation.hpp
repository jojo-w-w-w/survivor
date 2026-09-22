#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(sf::Vector2i frameSize, int frameCount, float frameDuration, sf::Vector2i startPosition = {0, 0});

    void update(sf::Sprite& sprite, float delta, int row, bool playing);

    void reset(sf::Sprite& sprite, int row = 0);

private:
    void applyFrame(sf::Sprite& sprite) const;

    sf::Vector2i frameSize;
    sf::Vector2i startPosition;

    int frameCount;
    float frameDuration;

    int currentFrame{0};
    int currentRow{0};
    float timer{0.f};
};