#include "Game.h"
#include "GameObject.h"
#include "TestLevel.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Input.h"

void Game::gameLoad() {
    sf::RenderWindow window(sf::VideoMode(1024, 768), "2-d platform");
    window.setFramerateLimit(60);

    loadTexture();

    TestLevel testlevel(*this);
    Input input;

    window.clear(sf::Color::Black);
    testlevel.loadLevel();
    while (window.isOpen())
    {
        deltatime = 0.016f;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        input.update();
        testlevel.update(deltatime, input);

        window.clear(sf::Color::Black);
        testlevel.draw(window);
        window.display();
    }
}