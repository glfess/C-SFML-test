#include "Entity.h"
#include "Ground.h"
#include "Obstacle.h"


void Entity::resolveCollision(const std::vector<std::shared_ptr<GameObject>>& objects, float dt)
{
    auto& physics = Physics::getInstance();

    onGround = false; // сброс флага перед обновлением

    // Движение по X
    pos.x += velocity.x * dt;
    shape->setPosition(pos);

    for (auto& other : objects)
    {
        if (this == other.get()) continue;

        sf::Vector2f correction;
        if (physics.computeCollision(getBounds(), other->getBounds(), velocity, correction))
        {
            pos.x += correction.x;
            velocity.x = 0.f;
            shape->setPosition(pos);
        }
    }

    // Движение по Y
    pos.y += velocity.y * dt;
    shape->setPosition(pos);

    for (auto& other : objects)
    {
        if (this == other.get()) continue;

        sf::Vector2f correction;
        if (physics.computeCollision(getBounds(), other->getBounds(), velocity, correction))
        {
            pos.y += correction.y;
            velocity.y = 0.f;
            shape->setPosition(pos);

            // Если корректировка вверх (стали на объект) и объект твердый
            if (correction.y < 0.f && other->getCollidable()) {
                onGround = true;
            }
        }
    }
}

