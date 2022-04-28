#include "Pickup.h"
#include "TextureHolder.h"
#include "Utils.h"
#include <iostream>
#include "../sound/SoundManager.h"

Pickup::Pickup(PickupTypes type)
	: type(type), isgetIt(false)
{
	std::string textureId;
	switch (this->type)
	{
	case PickupTypes::Ammo:
		textureId = "graphics/ammo_pickup.png";
		value = AMMO_START_VALUE;
		break;
	case PickupTypes::Health:
		textureId = "graphics/health_pickup.png";
		value = HEALETH_START_VALUE;
		break;
	}
	sprite.setTexture(TextureHolder::GetTexture(textureId));
	Utils::SetOrigin(sprite, Pivots::CC);

	Spawn(false);	
}

void Pickup::Update(float dt)
{
	timer -= dt;
	if (timer < 0)
	{
		Spawn(!spawned);
	}
}

void Pickup::Spawn(bool spawn)
{
	spawned = spawn;
	if (spawned)
	{
		timer = START_SENONDS_FOR_LIVE;

		int x = Utils::Random(arena.left + 50, arena.left + arena.width - 50);
		int y = Utils::Random(arena.top + 50, arena.top + arena.height - 50);

		sprite.setPosition(Vector2f(x, y));
		isgetIt = true;
	}
	else
	{
		timer = START_WAIT_TIME;
	}
}

int Pickup::GotIt()
{
	SoundManager::GetInstance()->pickupSound->play();
	isgetIt = false;
	return value;
}

void Pickup::SetArena(IntRect rect)
{
	arena = rect;
}

bool Pickup::IsSpawned()
{
	return spawned;
}

Sprite Pickup::GetSprite()
{
	return sprite;
}

FloatRect Pickup::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

PickupTypes Pickup::GetType()
{
	return type;
}

int Pickup::GetAmmo() const
{
	return AMMO_START_VALUE;
}

bool Pickup::GetIsGetIt() const
{
	return isgetIt;
}
