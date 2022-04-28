#pragma once
#include "SFML/Graphics.hpp"
#include "Blood.h"
#include <string>

using namespace sf;

class Player;

enum class ZombieTypes
{
	BLOATER,
	CHASER,
	CRAWLER,
	COUNT,
};

struct ZombieInfo
{
	ZombieTypes type;
	std::string textureFileName;
	float speed = 0;
	int health = 0;	// max health
};

class Zombie
{
private:
	ZombieTypes zombieType;

	Vector2f position;
	Sprite sprite;

	float speed;
	int health;

	bool alive;

	static std::vector<ZombieInfo> zombieInfo;
	static bool isInitInfo;

	Blood blood;
	bool isTime;
public:
	Zombie();

	bool OnHitted();
	bool IsAlive();
	void SetAlive(bool alive);

	void Spawn(float x, float y, ZombieTypes type);
	void Update(float dt, Vector2f playerPosition, IntRect arena);

	bool UpdateCollision(Time time, Player& player);

	FloatRect GetGlobalBound();
	Sprite GetSprite();
	float time;

	int GetHealth() const;
	Blood& GetBlood();
	bool IsTime();
};

