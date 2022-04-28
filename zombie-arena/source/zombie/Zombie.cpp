#include "Zombie.h"
#include "../utils/TextureHolder.h"
#include "../utils/Utils.h"
#include <iostream>
#include "../plyer/Player.h"

std::vector<ZombieInfo> Zombie::zombieInfo;
bool Zombie::isInitInfo = false;

Zombie::Zombie()
	: alive(true), health(0), speed(0), zombieType(ZombieTypes::BLOATER), isTime(true), time(3.f)
{
	if (!isInitInfo)
	{
		zombieInfo.resize((int)ZombieTypes::COUNT);
		{
			auto& info = zombieInfo[(int)ZombieTypes::BLOATER];
			info.type = ZombieTypes::BLOATER;
			info.textureFileName = "graphics/bloater.png";
			info.speed = 40.f;
			info.health = 5;
		}

		{
			auto& info = zombieInfo[(int)ZombieTypes::CHASER];
			info.type = ZombieTypes::CHASER;
			info.textureFileName = "graphics/chaser.png";
			info.speed = 70.f;
			info.health = 1;
		}

		{
			auto& info = zombieInfo[(int)ZombieTypes::CRAWLER];
			info.type = ZombieTypes::CRAWLER;
			info.textureFileName = "graphics/crawler.png";
			info.speed = 20.f;
			info.health = 3;
		}

		isInitInfo = true;
	}
}

bool Zombie::OnHitted()
{
	Player player;
	health -= player.GetDamage();
	if (health <= 0)
	{
		SetAlive(false);
	}
	return false;
}

bool Zombie::IsAlive()
{
	return alive;
}

void Zombie::SetAlive(bool _alive)
{
	alive = _alive;
}

void Zombie::Spawn(float x, float y, ZombieTypes type)
{
	auto& info = zombieInfo[(int)type];
	sprite.setTexture(TextureHolder::GetTexture(info.textureFileName));
	speed = info.speed * (Utils::Random(8, 11) * 0.1f);	// 속도 랜덤 부여
	health = info.health;

	position.x = x;
	position.y = y;

	Utils::SetOrigin(sprite, Pivots::CC);
	sprite.setPosition(position);
}
/****************************************
* 숙제입니당....ㅠㅠ
*****************************************/
void Zombie::Update(float dt, Vector2f playerPosition, IntRect arena)
{
	Vector2f positionTemp = position;
	// 플레이어의 위치에서 좀비의 위치를 빼준다음에
	// 그 값을 정규화를 한다.
	// 사용자 입력
	float x = playerPosition.x - position.x;

	float y = playerPosition.y - position.y;
	Vector2f dir(x, y);

	dir = Utils::Normalize(dir);


	position += dir * speed * dt;	// v = dt
	/**********************************************
	* 외곽 벽 충돌 처리
	**********************************************/
	if (position.x < arena.left + 50.f || position.x > arena.width - 50.f
		|| position.y < arena.top + 50.f || position.y > arena.height - 50.f)
	{
		position = positionTemp;
	}
	sprite.setPosition(position);

	float radian = atan2(dir.y, dir.x);
	float degree = radian * 180.f / 3.141592f;
	sprite.setRotation(degree);

	if (!alive && !blood.GetActive())
	{
		blood.SetPosition(position);
		blood.SetActive(true);
	}
	if (!alive)
	{
		time -= dt;
		if (time <= 0.f)
		{
			isTime = false;
		}
	}
}

bool Zombie::UpdateCollision(Time time, Player& player)
{
	if (sprite.getGlobalBounds().intersects(player.GetGobalBound()) && alive)
	{
		return player.OnHitted(time);
	}

	return false;
}

FloatRect Zombie::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

Sprite Zombie::GetSprite()
{
	return sprite;
}

int Zombie::GetHealth() const
{
	return health;
}

Blood& Zombie::GetBlood()
{
	return blood;
}

bool Zombie::IsTime()
{
	return isTime;
}
