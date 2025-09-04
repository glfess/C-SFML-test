#pragma once
#include "GameObject.h"
#include <sfml/Graphics.hpp>
#include "Game.h"
#include <vector>

class Obstacle :
    public GameObject
{
public:


    Obstacle(const sf::Texture* texture)
        : GameObject({ 0.f, 0.f }, texture) 
    {
        setShape(new sf::RectangleShape());
        setSize({ 50.f, 50.f });
        setTexture(*texture);
    }
public:
    void addPositions (sf::Vector2f newPos) 
    {
        this->positions.push_back(newPos);
    }

    void update(float deltatime) override
    {
        (void)deltatime;
    }

    void draw(sf::RenderWindow& window) override
    {
        if (getVisible() && shape)
        {
            shape->setPosition(pos);
            window.draw(*shape);
        }

    }
protected:
    std::vector<sf::Vector2f> positions;
};

