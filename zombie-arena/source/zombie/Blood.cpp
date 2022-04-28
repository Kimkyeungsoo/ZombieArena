#include "Blood.h"
#include "../utils/TextureHolder.h"
#include "../utils/Utils.h"

Blood::Blood()
	: textureId("graphics/blood.png"), isActive(false)
{
	sprite.setTexture(TextureHolder::GetTexture(textureId));
	Utils::SetOrigin(sprite, Pivots::CC);
}

void Blood::SetPosition(Vector2f zombieposition)
{
	sprite.setPosition(zombieposition);
}

Sprite Blood::GetSprite()
{
	return sprite;
}

void Blood::SetActive(bool active)
{
	isActive = active;
}

bool Blood::GetActive()
{
	return isActive;
}
