#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Blood
{
private:
	std::string textureId;

	Vector2f position;
	Sprite sprite;

	bool isActive;

public:
	Blood();

	void SetPosition(Vector2f zombieposition);

	FloatRect GetGlobalBound();
	Sprite GetSprite();

	void SetActive(bool active);
};

