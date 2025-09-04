//Player.h
#pragma once
#include "Entity.h"
#include <sfml/Graphics.hpp>
#include "Game.h"

class Player :
    public Entity
{

public:
    Player(sf::Vector2f position, const sf::Texture* texture)
        : Entity(position, texture)
    {
        setShape(new sf::RectangleShape());
        setSize({ 50.f, 50.f });
        setTexture(*texture);
        speed = 500.0f;
    }
    
    void update(float deltatime)
    {
        auto& physics = Physics::getInstance();

        velocity = physics.applyGravity(velocity, deltatime, gravity);

        velocity = physics.MaxSpeed(velocity, maxspeed);

        if (!movingX) velocity = physics.friction(velocity, friction);

        pos += velocity * deltatime;

        std::cout << "position.y " << pos.y << std::endl;

        shape->setPosition(pos);

        movingX = false;
    }

    void draw(sf::RenderWindow& window) override
    {
        if (shape && getVisible())
        {
            window.draw(*shape);
        }
    }

    void HandleInput(const Input& input, float deltatime) {
        (void)deltatime;

        auto& physics = Physics::getInstance();
        if (input.AKeyPressed()) 
        {
            velocity = physics.moveX(velocity, -speed);
            movingX = true;
        }
        if (input.DKeyPressed()) 
        {
            velocity = physics.moveX(velocity, speed);
            movingX = true;
        }

        if (input.SpaceKeyPressed() && onGround == true)
        {
            velocity.y = physics.applyJump(jumpStrength);
            onGround = false;

        }
        if (input.ShiftKeyPressed()) 
        {
            maxspeed = 500.f;
        }
        else
        {
            maxspeed = 200.f;
        }


    }
private:
};

