#pragma once
#include "GameObject.h"
#include <vector>
#include "Physics.h"

class Entity :
    public GameObject
{
public:

    Entity(sf::Vector2f position, const sf::Texture* texture)
        : GameObject(position, texture),
        health(100), speed(200.f), maxspeed(200.f), jumpStrength(400.f)
    {}

    float getSpeed() const { return speed; }
    void setSpeed(float newSpeed) { speed = newSpeed; }

    float getJumpStrength() const { return jumpStrength; }
    void setJumpStrength(float newJumpStrength) { jumpStrength = newJumpStrength; }

    sf::Vector2f getVelocity() const { return velocity; }
    void setVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; }

    float getGravity() const { return gravity; }
    void setGravity(float newGravity) { gravity = newGravity; }

    float getFriction() const { return friction; }
    void setFriction(float newFriction) { friction = newFriction; }

    bool getOnGround() const { return onGround; }
    void setOnGround(bool newOnGround) { onGround = newOnGround; }

    bool getMovingX() const { return movingX; }
    void setMovingX(bool newMovingX) { movingX = newMovingX; }

    float getmaxSpeed() const { return maxspeed; }
    void setmaxSpeed(float newmaxSpeed) { maxspeed = newmaxSpeed; }

    int getHealth() const { return health; };
    void setHealth(int setHealth) { health = setHealth; };

    void resolveCollision(const std::vector<std::shared_ptr<GameObject>>& objects,
        float dt);

protected:
    sf::Vector2f velocity;
    float speed;
    float jumpStrength;
    float maxspeed;
    float gravity = 980.f;
    float friction = 0.6f;
    int health;
    bool onGround = true;
    bool movingX = false;
};

