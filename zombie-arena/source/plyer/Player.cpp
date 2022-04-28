#include "Player.h"
#include "../utils/Utils.h"
#include "../utils/InputMgr.h"
#include <cmath>
#include "../utils/TextureHolder.h"
#include <iostream>
#include <algorithm>
#include "../utils/Pickup.h"

Player::Player()
	: speed(START_SPEED), health(START_HEALTH), maxHealth(START_HEALTH), immuneMs(START_IMMUNE_MS), arena(), resolution(), tileSize(0), textureFileName("graphics/player.png"), distanceToMuzzle(45.f), damage(START_DAMAGE)
{
	//texture.loadFromFile("graphics/player.png");
	sprite.setTexture(TextureHolder::GetTexture(textureFileName));
	Utils::SetOrigin(sprite, Pivots::CC);

	for (int i = 0; i < BULLET_CACHE_SIZE; ++i)
	{
		unuseBullets.push_back(new Bullet());
	}


	totalAmmo = 30;
	haveAmmo = totalAmmo;
	reloadedAmmo = 12 * level_Reload;
}

Player::~Player()
{
	for (auto bullet : unuseBullets)
	{
		delete bullet;
	}
	unuseBullets.clear();
	for (auto bullet : useBullets)
	{
		delete bullet;
	}
	useBullets.clear();
}

void Player::Shoot(Vector2f dir)
{
/**********************
* 재장전
***********************/
	if (haveAmmo == 0)
	{
		return;
	}
	// 발사 시 마다 장탄수 감소
	haveAmmo--;




	// 가져오고 초기화 발사 까지
	dir = Utils::Normalize(dir);

	Vector2f spawnPos = position + dir * distanceToMuzzle;

	if (unuseBullets.empty())
	{
		for (int i = 0; i < BULLET_CACHE_SIZE; ++i)
		{
			unuseBullets.push_back(new Bullet());
		}
	}
	Bullet* bullet = unuseBullets.front();
	unuseBullets.pop_front();
	useBullets.push_back(bullet);
	bullet->Shoot(spawnPos, dir);
}

void Player::Spawn(IntRect arena, Vector2i res, int tileSize)
{
	this->arena = arena;
	resolution = res;
	this->tileSize = tileSize;

	position.x = this->arena.width * 0.5f;
	position.y = this->arena.height * 0.5f;
}

bool Player::OnHitted(Time timeHit)
{
	if (timeHit.asMilliseconds() - lastHit.asMilliseconds() > immuneMs)
	{
		std::cout << timeHit.asSeconds() << std::endl;
		lastHit = timeHit;
		health -= 10;
		return true;
	}
	return false;
}

Time Player::GetLastTime() const
{
	return lastHit;
}

FloatRect Player::GetGobalBound() const
{
	return sprite.getGlobalBounds();
}

Vector2f Player::GetPosition() const
{
	return position;
}

float Player::GetRotation() const
{
	return sprite.getRotation();
}

Sprite Player::GetSprite() const
{
	return sprite;
}

int Player::GetHealth() const
{
	return health;
}

int Player::GetDamage() const
{
	return damage;
}

void Player::Update(float dt, IntRect arena)
{
	Vector2f positionTemp = position;
	// 사용자 입력
	float h = InputMgr::GetAxis(Axis::Horizontal);
	float v = InputMgr::GetAxis(Axis::Vertical);
	Vector2f dir(h, v); // 사용자 입력

	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length > 1.f)
	{
		dir /= length;
	}

	// 이동
	position += dir * speed * dt;	// v = dt
	/**********************************************
	* 외곽 벽 충돌 처리
	**********************************************/
	if (position.x < arena.left + 50.f || position.x > arena.width - 50.f)
	{
		position.x = positionTemp.x;
	}
	if (position.y < arena.top + 50.f || position.y > arena.height - 50.f)
	{
		position.y = positionTemp.y;
	}
	sprite.setPosition(position);
	// 회전
	// 두 벡터 사이의 사이각을 구하는것은 아크탄젠트사용
	Vector2i mousePos = InputMgr::GetMousePosition();
	Vector2i mouseDir;
	mouseDir.x = mousePos.x - resolution.x * 0.5f;
	mouseDir.y = mousePos.y - resolution.y * 0.5f;
	//mouseDir.x = mousePos.x - position.x;
	//mouseDir.y = mousePos.y - position.y;

	float radian = atan2(mouseDir.y, mouseDir.x);
	float degree = radian * 180.f / 3.141592f;

	sprite.setRotation(degree);


	/**********************
	* 총알
	***********************/
	if (InputMgr::GetMouseButtonDown(Mouse::Button::Left))
	{
		Shoot(Vector2f(mouseDir.x, mouseDir.y));
	}

/**********************
* 재장전
***********************/
	if (InputMgr::GetKeyDown(Keyboard::R))
	{
		Reloading = true;
	}
	if (Reloading)
	{
		timer -= dt;
		if (timer < 0)
		{
			Reloading = false;
			Reload();
			// timer 초기화
			timer = 3;
		}
	}



	auto it = useBullets.begin();
	while (it != useBullets.end())
	{
		Bullet* bullet = *it;
		bullet->Update(dt, arena);

		if (!bullet->IsActive())
		{
			it = useBullets.erase(it);
			unuseBullets.push_back(bullet);
		}
		else
		{
			++it;
		}
	}
}

bool Player::UpdateCollision(const std::list<Pickup*> items)
{
	FloatRect bounds = sprite.getGlobalBounds();
	bool isCollided = false;
	for (auto item : items)
	{
		if (bounds.intersects(item->GetGlobalBound()))
		{
			item->GotIt();
		}
		isCollided = true;
	}
	return false;
}

bool Player::UpdateCollision(const std::vector<Zombie*>& zombies)
{
	bool isCollided = false;
	for (auto bullet : useBullets)
	{
		if (bullet->UpdateCollision(zombies))
		{
			isCollided = true;
		}
	}

	return isCollided;
}

void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
	for (auto bullet : useBullets)
	{
		window.draw(bullet->GetShape());
	}
}

void Player::GetHealthItem(int amount)
{
	health += amount;
	if (health > maxHealth)
	{
		health = maxHealth;
	}

	if (health < 0)
	{
		health = 0;
	}
}

void Player::UpgradeSpeed()
{
	speed += START_SPEED * 0.2;
}

void Player::UpgradeMaxHealth()
{
	maxHealth += START_HEALTH * 0.2;
}

void Player::Reload()
{
	haveAmmo = totalAmmo + reloadedAmmo;
}




