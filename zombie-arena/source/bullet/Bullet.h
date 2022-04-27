#pragma once

#include "SFML/Graphics.hpp"
#include <string>

using namespace sf;

class Zombie;

class Bullet
{
private:
	const float BULLET_SPEED = 2000.f;
	const float DEFAULT_DISTANCE = 1000.f;	// 이동거리

	RectangleShape shape;
	Vector2f direction;
	Vector2f position;

	bool isActive;
	float speed;

	float distance;
public:
	Bullet();
	
	void SetActive(bool active);
	void Shoot(Vector2f pos, Vector2f dir);
	void Stop();
	void Update(float dt);
	
	bool UpdateCollision(const std::vector<Zombie*>& zombies);

	bool IsActive();
	RectangleShape GetShape();
};

