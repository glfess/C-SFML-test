#pragma once

#include <vector>
#include "Entity.h"

class Physics
{
public:
	static Physics& getInstance() {
		static Physics instance;
		return instance;
	};

	void update(float deltatime)
	{
		(void)deltatime;
	};

	sf::Vector2f applyGravity(const sf::Vector2f& velocity, float deltatime, float gravity) const
	{
		sf::Vector2f newVel = velocity;
		newVel.y += gravity * deltatime;
		return newVel;
	}

	float applyJump(float jumpStrength) const
	{
		return -jumpStrength;
	}

	sf::Vector2f moveX(const sf::Vector2f& velocity, float moveSpeed) const 
	{
		sf::Vector2f newVel = velocity;
		newVel.x += moveSpeed;
		return newVel;
	}

	sf::Vector2f friction(const sf::Vector2f& velocity, float friction) const
	{
		sf::Vector2f newVel = velocity;
		newVel.x *= friction;
		return newVel;
	}

	sf::Vector2f MaxSpeed(const sf::Vector2f& velocity, float maxSpeed) const
	{
		sf::Vector2f newVel = velocity;
		if (newVel.x > maxSpeed) newVel.x = maxSpeed;
		if (newVel.x < -maxSpeed) newVel.x = -maxSpeed;
		return newVel;
	}

	bool computeCollision(const sf::FloatRect& a, const sf::FloatRect& b,
		const sf::Vector2f& velocity, sf::Vector2f& correction);
private:
	Physics() = default;
	Physics(const Physics&) = delete;
	Physics& operator=(const Physics&) = delete;


};

