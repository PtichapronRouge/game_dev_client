#ifndef INITSTATE_HPP
#define INITSTATE_HPP

#include "headers/state.hpp"

#include <SFML/Graphics/Color.hpp>

class InitState : public State
{
    public:
                        InitState(State::Context context, StateStack& statestack);
                        ~InitState();

        bool            handleEvent(const sf::Event& event);
        bool            update(sf::Time dt);
        void            draw();

    private:
        sf::Color       mDisplayColor;
};

#endif // INITSTATE_HPP
