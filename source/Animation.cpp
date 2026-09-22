#include "Animation.hpp"

Animation::Animation(sf::Vector2i frameSize, int frameCount, float frameDuration, sf::Vector2i startPosition) :
frameSize(frameSize),
startPosition(startPosition),
frameCount(frameCount),
frameDuration(frameDuration)
{

}

void Animation::update(sf::Sprite& sprite, float delta, int row, bool playing)
{
    // 改变朝向时重新播放
    if(row != currentRow)
    {
        currentRow = row;
        currentFrame = 0;
        timer = 0.f;
    }

    // 停止移动时显示当前方向第一帧
    if(!playing)
    {
        currentFrame = 0;
        timer = 0.f;
        applyFrame(sprite);
        return;
    }

    timer += delta;

    while(timer >= frameDuration)
    {
        timer -= frameDuration;
        currentFrame = (currentFrame + 1) % frameCount;
    }

    applyFrame(sprite);
}

void Animation::reset(sf::Sprite& sprite, int row)
{
    currentRow = row;
    currentFrame = 0;
    timer = 0.f;

    applyFrame(sprite);
}

void Animation::applyFrame(sf::Sprite& sprite) const
{
    const sf::Vector2i framePosition
    {
        startPosition.x + currentFrame * frameSize.x,
        startPosition.y + currentRow * frameSize.y
    };

    sprite.setTextureRect
    (
        sf::IntRect(framePosition, frameSize)
    );
}