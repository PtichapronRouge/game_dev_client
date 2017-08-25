#include "headers/statestack.hpp"
#include <iostream>
#include <cassert>

StateStack::PendingChange::PendingChange(Action action, States::ID stateID) : action(action), stateID(stateID) {}

StateStack::StateStack(State::Context context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories()
{

}

void StateStack::handleEvent(const sf::Event &event)
{
    for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if((*itr)->handleEvent(event))
            break;
    }

    applyPendingChanges();
}

void StateStack::update(sf::Time dt)
{
    for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if((*itr)->update(dt))
            break;
    }

    applyPendingChanges();
}

void StateStack::draw()
{
    for(State::Ptr& state : mStack)
        state->draw();
}

void StateStack::pushState(States::ID stateID)
{
    mPendingList.push(PendingChange(Action::Push, stateID));
}

void StateStack::popState()
{
    mPendingList.push(PendingChange(Action::Pop));
}

void StateStack::clearStates()
{
    mPendingList.push(PendingChange(Action::Clear));
}

bool StateStack::isEmpty() const
{
    return mStack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());

    return found->second();
}

void StateStack::applyPendingChanges()
{
    while(!mPendingList.empty())
    {
        switch(mPendingList.front().action)
        {
            case Action::Push:
                mStack.push_back(createState(mPendingList.front().stateID));
                break;

            case Action::Pop:
                mStack.pop_back();
                break;

            case Action::Clear:
                mStack.clear();
                break;

            default:
                break;
        }
        mPendingList.pop();
    }
}
