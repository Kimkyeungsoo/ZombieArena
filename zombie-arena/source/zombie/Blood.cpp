#include "Blood.h"
#include "../utils/TextureHolder.h"

Blood::Blood()
	: textureId("graphics/blood.png"), isActive(false)
{
	sprite.setTexture(TextureHolder::GetTexture(textureId));
	//sprite.setPosition(zombieposition);
}

void Blood::SetPosition(Vector2f zombieposition)
{
	sprite.setPosition(zombieposition);
}

FloatRect Blood::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

Sprite Blood::GetSprite()
{
	return sprite;
}
