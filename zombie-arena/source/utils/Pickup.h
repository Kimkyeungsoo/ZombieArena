#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

enum class PickupTypes
{
	Ammo,
	Health,
};

class Pickup
{
private:
	const int HEALETH_START_VALUE = 50;
	const int AMMO_START_VALUE = 12;
	const float START_WAIT_TIME = 10.f;
	const float START_SENONDS_FOR_LIVE = 5.f;

	PickupTypes type;

	Sprite sprite;
	IntRect arena;

	int value;

	bool spawned;
	float timer;

	bool isgetIt;
public:
	Pickup(PickupTypes type);

	void Update(float dt);

	void Spawn(bool spawn);
	int GotIt();

	void SetArena(IntRect rect);
	bool IsSpawned();
	Sprite GetSprite();
	FloatRect GetGlobalBound();
	PickupTypes GetType();

	int GetAmmo() const;
	bool GetIsGetIt() const;
};

