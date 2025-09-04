#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Game
{
public:

	void gameLoad();

	void loadTexture() {
        if (!PlayerSprite.loadFromFile("resources/playerSprite.png"))
        {
            std::cerr << "�� ������� ��������� ������ ������";
            std::cout << "������� Enter ��� ������...";
            std::cin.get();
            exit(-1);
        }

        if (!GroundSprite.loadFromFile("resources/groundSprite.png"))
        {
            std::cerr << "�� ������� ��������� ������ �����";
            std::cout << "������� Enter ��� ������...";
            std::cin.get();
            exit(-1);
        }

        if (!ObstacleSprite.loadFromFile("resources/boxSprite.png"))
        {
            std::cerr << "�� ������� ��������� ������ �����������";
            std::cout << "������� Enter ��� ������...";
            std::cin.get();
            exit(-1);
        }
	}

    const sf::Texture& getPlayerSprite() { return PlayerSprite; }
    const sf::Texture& getGroundSprite() { return GroundSprite; }
    const sf::Texture& getObstacleSprite() { return ObstacleSprite; }

private:
    sf::Texture PlayerSprite;
    sf::Texture GroundSprite;
    sf::Texture ObstacleSprite;
    sf::Clock clock;
    float deltatime;
};

