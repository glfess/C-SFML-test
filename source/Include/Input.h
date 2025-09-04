//Input.h
#pragma once
#include <sfml/Graphics.hpp>
class Input
{
public:
	void update(){
		isAKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		isDKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		isSpaceKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		isShiftKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
		//isRestartKeyPressed = sf::Event::KeyPressed;
	}

	bool AKeyPressed() const { return isAKeyPressed; };
	bool DKeyPressed() const { return isDKeyPressed; };
	bool SpaceKeyPressed() const { return isSpaceKeyPressed; };
	bool ShiftKeyPressed() const { return isShiftKeyPressed; };
	//bool RestartKeyPressed() const { return isRestartKeyPressed; };

private:
	bool isAKeyPressed = false;
	bool isDKeyPressed = false;
	bool isSpaceKeyPressed = false;
	bool isShiftKeyPressed = false;
	//bool isRestartKeyPressed = false;
};

