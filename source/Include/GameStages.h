#pragma once
#include <sfml/Graphics.hpp>
#include "Input.h"

class GameStages
{
public:
	virtual void loadLevel() = 0;

	virtual void update(float deltatime, const Input& input) = 0;
protected:
};

