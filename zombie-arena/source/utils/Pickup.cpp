#include "Pickup.h"
#include "TextureHolder.h"
#include "Utils.h"
#include <iostream>

Pickup::Pickup(PickupTypes type)
	: type(type)
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

		int x = Utils::Random(arena.left, arena.left + arena.width);
		int y = Utils::Random(arena.top, arena.top + arena.height);

		sprite.setPosition(Vector2f(x, y));
	}
	else
	{
		timer = START_WAIT_TIME;
	}
}

int Pickup::GotIt()
{
	switch (type)
	{
	case PickupTypes::Ammo:
		std::cout << "Ammo" << std::endl;
		break;
	case PickupTypes::Health:
		std::cout << "Health" << std::endl;
		break;
	default:
		break;
	}
	// 충돌 처리
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
