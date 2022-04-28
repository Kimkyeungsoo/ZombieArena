#include "Bullet.h"
#include "../utils/Utils.h"
#include "../zombie/Zombie.h"

Bullet::Bullet()
	: speed(BULLET_SPEED), isActive(false)
{
	shape.setSize(Vector2f(7, 3));
	Utils::SetOrigin(shape, Pivots::CC);
	shape.setFillColor(Color::Yellow);
}

void Bullet::SetActive(bool active)
{
	isActive = active;
}

bool Bullet::IsActive()
{
	return isActive;
}

void Bullet::Shoot(Vector2f pos, Vector2f dir)
{
	SetActive(true);

	distance = 0.f;	// �̵��Ÿ�

	position = pos;
	shape.setPosition(position);
	direction = Utils::Normalize(dir);	// normalized
	float dgree = Utils::GetAngle(position, position + direction);
	shape.setRotation(dgree);
}

void Bullet::Stop()
{
	SetActive(false);
}

void Bullet::Update(float dt, IntRect arena)
{
	position += direction * speed * dt;
	shape.setPosition(position);

	distance += speed * dt;
	if (distance > DEFAULT_DISTANCE)
	{
		Stop();
	}
	if (position.x < arena.left + 50.f || position.x > arena.width - 50.f
		|| position.y < arena.top + 50.f || position.y > arena.height - 50.f)
	{
		Stop();
	}
}
/**********************************************
* �浹
***********************************************/
bool Bullet::UpdateCollision(const std::vector<Zombie*>& zombies)
{
	FloatRect bounds = shape.getGlobalBounds();

	for (auto zombie : zombies)
	{
		if (zombie->IsAlive())
		{
			if (bounds.intersects(zombie->GetGlobalBound()))
			{
				zombie->OnHitted();
				Stop();
				return true;
			}
		}
	}
	return false;
}

RectangleShape Bullet::GetShape()
{
	return shape;
}

