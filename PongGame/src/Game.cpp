#include"PCH.h"
#include "MenuState.h"
#include "Game.h"


Game::Game() : deltaTime {0}
{
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Pong");
    window->setFramerateLimit(60);
    bool mp = false;
    states.push(std::make_unique<MenuState>(window, &states, mp));
}

Game::~Game()
{
    delete window;
    while (!states.empty())
        states.pop();
}

void Game::UpdateDt()
{
    deltaTime = dtClock.restart().asSeconds();
}

void Game::UpdateSFMLEvents()
{
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void Game::Update()
{
    UpdateSFMLEvents();

    if (!states.empty()) {
        states.top()->Update(deltaTime);
        //if EndState
        if (states.top()->GetQuit()) {
            states.top()->EndState();
            states.pop();
        }
    }
    else {
        window->close();
    }
}

void Game::Render()
{
    window->clear(sf::Color::White);

    if (!states.empty())
        states.top()->Render();

    window->display();
}

void Game::Run()
{
    while (window->isOpen()) {
        UpdateDt();
        Update();
        Render();
    }
}



