#include "headers/initstate.hpp"

InitState::InitState(State::Context context, StateStack& statestack)
: State(context, statestack)
, mDisplayColor(sf::Color::Red)
{

}

InitState::~InitState()
{

}

bool InitState::handleEvent(const sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::Escape:
                contextWindow()->close();
                break;

            case sf::Keyboard::Up:
                mDisplayColor = sf::Color::Red;
                break;

            case sf::Keyboard::Down:
                mDisplayColor = sf::Color::Blue;
                break;

            default:
                mDisplayColor = sf::Color::Black;
                break;
        }
    }

    return true;
}

bool InitState::update(sf::Time dt)
{
    return true;
}

void InitState::draw()
{
    contextWindow()->clear(mDisplayColor);
}
