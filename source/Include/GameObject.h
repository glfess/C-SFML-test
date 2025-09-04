#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Input.h"


class GameObject
{
public:
	GameObject(sf::Vector2f position, const sf::Texture* texture = nullptr)
		: shape(nullptr), pos(position), size({0.f, 0.f}),
		isVisible(true), isCollidable(true), isEnabled(true) {
		if (texture) setTexture(*texture);
	}

	virtual void update(float deltatime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	sf::Vector2f getCoordinates() const { return pos; }
	void setCoordinates(sf::Vector2f pos1) { 
		pos = pos1;
		if (shape) shape->setPosition(pos); }

	bool getVisible() const { return isVisible; }
	void setVisible(bool newVisible) { isVisible = newVisible; }

	bool getCollidable() const { return isCollidable; }
	void setCollidable(bool newCollidable) { isCollidable = newCollidable; }

	bool getEnable() const { return isEnabled; }
	void setEnable(bool newEnabled) { isEnabled = newEnabled; }

	sf::Shape* getShape() const { return shape.get(); }

	void setTexture(const sf::Texture& texture) { 
		sf::Vector2u textureSize = texture.getSize();
		if (!shape) return;
		shape->setTexture(&texture);

		if (auto rectangle = dynamic_cast<sf::RectangleShape*>(shape.get()))
			rectangle->setSize(sf::Vector2f(static_cast<float>(textureSize.x), static_cast<float>(textureSize.y)));

		if (auto circle = dynamic_cast<sf::CircleShape*>(shape.get())) {
			circle->setRadius(static_cast<float>(textureSize.x) / 2.f);
			circle->setOrigin(static_cast<float>(textureSize.x) / 2.f, static_cast<float>(textureSize.y) / 2.f);
		}

		if (auto convex = dynamic_cast<sf::ConvexShape*>(shape.get()))
		{
			
			sf::FloatRect bounds = convex->getLocalBounds();
			convex->setScale(static_cast<float>(textureSize.x) / bounds.width, static_cast<float>(textureSize.y) / bounds.height);
		}
	}
	sf::Texture getSprite() { return GOSprite; }

	void setSize(const sf::Vector2f newSize) {
		size = newSize;
		if (!shape) return;

		if (auto rectangle = dynamic_cast<sf::RectangleShape*>(shape.get()))
		{
			rectangle->setSize(size);
		}
		
		if (auto circle = dynamic_cast<sf::CircleShape*>(shape.get()))
		{
			circle->setRadius(size.x / 2);
			circle->setOrigin(circle->getRadius(), circle->getRadius());
		}

		if (auto convex = dynamic_cast<sf::ConvexShape*>(shape.get()))
		{
			sf::FloatRect bounds = convex->getGlobalBounds();
			convex->setScale(size.x / bounds.width, size.y / bounds.height);
		}


	}
	sf::Vector2f getSize() { return size; }

	void setShape(sf::Shape* newShape)
	{
		shape.reset(newShape);
		if (shape)
		{
			shape->setPosition(size);
			if (GOSprite.getSize().x > 0 && GOSprite.getSize().y > 0)
				shape->setTexture(&GOSprite);
			setSize(size);
		}
	}

	void setFillColor(sf::Color colortype) {
		if (shape) shape->setFillColor(colortype);
	}

	sf::FloatRect getBounds() const
	{
		return shape->getGlobalBounds();
	}

protected:
	
	sf::Vector2f size;
	sf::Vector2f pos;
	sf::Texture GOSprite;
	bool isVisible;
	bool isCollidable = true;
	bool isEnabled;

	std::unique_ptr<sf::Shape> shape;
};