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
    if (!states.empty()) 
        states.pop_back();
}

void StateStack::changeState(std::unique_ptr<GameState> state) 
{
    states.clear();
    pushState(std::move(state));
}

void StateStack::handleInput(const sf::Event& event)
{
    if (!states.empty())
        states.back()->handleInput(event);
}

void StateStack::update(sf::Time delta) 
{
    if (!states.empty())
        states.back()->update(delta);
}

void StateStack::render() 
{
    if (!states.empty()) 
        states.back()->render();
}

