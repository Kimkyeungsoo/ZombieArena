#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(RenderWindow& window) = 0;
	virtual void Clear() = 0;
};

