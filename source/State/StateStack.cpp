#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "StateStack.hpp"

StateStack::StateStack() = default;
StateStack::~StateStack() = default;

void StateStack::pushState(std::unique_ptr<GameState> state) 
{
    states.push_back(std::move(state));
}

void StateStack::popState() 
{
    popRequested = true;
}

void StateStack::changeState(std::unique_ptr<GameState> state) 
{
    nextState = std::move(state);
}

void StateStack::applyPendingChanges()
{
    if(nextState)
    {
        states.clear();
        states.push_back(std::move(nextState));
    }
    else if(popRequested)
    {
        if(!states.empty())
        {
            states.pop_back();
        }
    }
    popRequested = false;
}

void StateStack::handleInput(const sf::Event& event)
{
    if (!states.empty())
        states.back()->handleInput(event);
    
    // 当前状态的 handleInput 已经返回，现在才切换
    applyPendingChanges();
}

void StateStack::update(sf::Time delta) 
{
    if (!states.empty())
        states.back()->update(delta);

    // 当前状态的 update 已经返回，现在才切换
    applyPendingChanges();
}

void StateStack::render() 
{
    if (!states.empty()) 
        states.back()->render();
}

