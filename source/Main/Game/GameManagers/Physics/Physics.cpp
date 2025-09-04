#include "Physics.h"
#include <vector>
#include "Entity.h"
#include "GameObject.h"

bool Physics::computeCollision(const sf::FloatRect& a, const sf::FloatRect& b,
    const sf::Vector2f& velocity, sf::Vector2f& correction)
{
    if (!a.intersects(b))
        return false;

    float dx1 = (b.left + b.width) - a.left;
    float dx2 = (a.left + a.width) - b.left;
    float dy1 = (b.top + b.height) - a.top;
    float dy2 = (a.top + a.height) - b.top;

    float minX = std::min(dx1, dx2);
    float minY = std::min(dy1, dy2);

    correction = { 0.f, 0.f };

    if (minX < minY) {
        // коллизия по X
        if (velocity.x > 0)       correction.x = -minX;
        else if (velocity.x < 0) correction.x = minX;
    }
    else {
        // коллизия по Y
        if (velocity.y > 0)       correction.y = -minY ;
        else if (velocity.y < 0) correction.y = minY;
    }

    return true;
}

