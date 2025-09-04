#include <sfml/Graphics.hpp>
#include "Testlevel.h"

void TestLevel::draw(sf::RenderWindow& window) {
    for (auto& obj : objects) {
        obj->draw(window);
    }
};

void TestLevel::loadLevel() {
    auto& playerTexture = game.getPlayerSprite();
    auto& obstacleTexture = game.getObstacleSprite();
    auto& groundTexture = game.getGroundSprite();

    std::unique_ptr<Player> player = std::make_unique<Player>(sf::Vector2f(200.f, 200.f),
        &game.getPlayerSprite());
    player->setShape(new sf::RectangleShape);
    player->setTexture(playerTexture);
    player->setSize({ 50.f, 50.f });
    player->setCoordinates({ 500.f, 500.f });
    objects.push_back(std::move(player));

    for (auto& pos : obsPositions)
    {
        auto obs = std::make_unique<Obstacle>(&game.getObstacleSprite());
        obs->setShape(new sf::RectangleShape());
        obs->setTexture(obstacleTexture);
        obs->setSize({ 50.f, 50.f });
        obs->setCoordinates(pos); // устанавливаем текущую позицию
        objects.push_back(std::move(obs));
    }

    for (int i = 0; i < 21; ++i)
    {
        auto ground_tile = std::make_unique<Ground>(&game.getGroundSprite());
        ground_tile->setShape(new sf::RectangleShape());
        ground_tile->setTexture(groundTexture);
        ground_tile->setSize({ 50.f, 50.f });
        ground_tile->setCoordinates({ i * 50.f, 718 });
        objects.push_back(std::move(ground_tile));
    }
}

void TestLevel::update(float deltatime, const Input& input)
{
    // 1. Обработка ввода и обновление состояния объектов
    for (auto& obj : objects)
    {
        if (auto player = dynamic_cast<Player*>(obj.get()))
            player->HandleInput(input, deltatime);

        obj->update(deltatime);
    }

    // 2. Проверка коллизий
    for (auto& obj : objects)
    {
        if (auto entity = dynamic_cast<Entity*>(obj.get()))
        {
            // Передаем в resolveCollisions весь список объектов, кроме самого себя
            std::vector<std::shared_ptr<GameObject>> others;
            for (auto& other : objects)
                if (other.get() != obj.get())
                    others.push_back(std::shared_ptr<GameObject>(other.get(), [](GameObject*) {}));

            entity->resolveCollision(others, deltatime);
        }
    }
}


