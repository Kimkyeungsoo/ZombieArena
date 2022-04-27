#pragma once
#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include "../bullet/Bullet.h"
#include <list>

using namespace sf;

class Pickup;

class Player
{

private:
	const float START_SPEED = 300.f;
	const int START_HEALTH = 100;
	const float START_IMMUNE_MS = 500.f;

	Vector2f position;

	std::string textureFileName;
	Sprite sprite;

	Vector2i resolution;
	IntRect arena;

	int tileSize;

	Vector2f lastDir; // 마지막에 입력한 방향
	float speed;	// max

	int health;
	int maxHealth;
	float immuneMs;
	//bool inmune;

	Time lastHit;

	const int BULLET_CACHE_SIZE = 1000;
	std::list<Bullet*> unuseBullets;	// 사용하지 않은 불릿
	std::list<Bullet*> useBullets;	//	사용중인 불릿

	float distanceToMuzzle;
public:
	Player();
	~Player();

	void Shoot(Vector2f dir);

	void Spawn(IntRect arena, Vector2i res, int TileSize);

	bool OnHitted(Time timeHit);

	Time GetLastTime() const;
	FloatRect GetGobalBound() const;
	Vector2f GetPosition() const;
	float GetRotation() const;
	Sprite GetSprite() const;
	int GetHealth() const;

	void Update(float dt, IntRect arena);
	bool UpdateCollision(const std::list<Pickup*> items);
	bool UpdateCollision(const std::vector<Zombie*>& zombies);

	void Draw(RenderWindow& window);

	void GetHealthItem(int amount);

	void UpgradeSpeed();
	void UpgradeMaxHealth();
};
