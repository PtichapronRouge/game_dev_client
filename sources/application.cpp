#include "headers/application.hpp"
#include "headers/initstate.hpp"

Application::Application()
: mWindow(sf::VideoMode(800, 640), "Asym Game")
, mStateStack(State::Context(mWindow))
{
    mStateStack.registerState<InitState>(States::ID::Init);

    mStateStack.pushState(States::ID::Init);
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    sf::Time timePerFrame = sf::seconds(1.f/60.f);

    while(mWindow.isOpen())
    {
        sf::Time dt = clock.restart();  // Temps écoulé depuis la frame précédente
        timeSinceLastUpdate += dt;      // Temps écoulé depuis la dernière actualisation

        while(timeSinceLastUpdate > timePerFrame)   //Boucle permettant de pallier aux problèmes de latence
        {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();

            update(timePerFrame);
        }

        render();
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event)) //boucle de gestion des evenements claviers
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();

        mStateStack.handleEvent(event);
    }
}

void Application::render()
{
    mWindow.clear(sf::Color::Black);

    mWindow.getDefaultView();

    mStateStack.draw();

    mWindow.display();
}
