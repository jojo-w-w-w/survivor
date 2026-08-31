#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "GameState.hpp"

class StateStack 
{
public:
    StateStack();
    ~StateStack();

    void pushState(std::unique_ptr<GameState> state);
   
    void popState();

    void changeState(std::unique_ptr<GameState> state);

    void handleInput(const sf::Event& event);

    void update(sf::Time delta);
   
    void render();
    
private:
    std::vector<std::unique_ptr<GameState>> states;
    
};