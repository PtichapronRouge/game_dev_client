#include "headers/state.hpp"
#include "headers/statestack.hpp"

State::Context::Context(sf::RenderWindow &window) : window(&window) {}

State::State(Context context, StateStack& statestack)
: mContext(context)
, mStateStack(&statestack)
{
}

State::~State()
{}

void State::requestStackPush(States::ID id) const
{
    mStateStack->pushState(id);
}

void State::requestStackPop() const
{
    mStateStack->popState();
}

void State::requestStackClear() const
{
    mStateStack->clearStates();
}

sf::RenderWindow* State::contextWindow() const
{
    return mContext.window;
}
