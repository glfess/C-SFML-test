#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Ground.h"
#include "Obstacle.h"
#include "UI.h"
#include "Background.h"
#include "GameStages.h"
#include "GameObject.h"
#include <vector>

class TestLevel :
    public GameStages
{
    Game& game;

    std::vector<std::unique_ptr<GameObject>> objects;
public:

    TestLevel(Game& g) : game(g) {}

    void draw(sf::RenderWindow& window);

    void loadLevel() override;

    void update(float deltatime, const Input& input) override;
  
    std::vector<sf::Vector2f> obsPositions = {
    {100.f, 668.f},
    {300.f, 668.f},
    {500.f, 668.f},
    {700.f, 668.f}
    };
};

