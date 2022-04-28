#include "Player.h"
#include "../utils/Utils.h"
#include "../utils/TextureHolder.h"
#include "../utils/GameLevelData.h"
#include "../utils/Pickup.h"
#include "../utils/InputMgr.h"
#include "../utils/SceneManager.h"
#include "../utils/ViewManager.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Player::Player()
	: speed(START_SPEED), health(START_HEALTH), maxHealth(START_HEALTH), immuneMs(START_IMMUNE_MS), arena(), 
	resolution(), tileSize(0), textureFileName("graphics/player.png"), distanceToMuzzle(45.f), damage(START_DAMAGE)
{
	sprite.setTexture(TextureHolder::GetTexture(textureFileName));
	Utils::SetOrigin(sprite, Pivots::CC);

	for (int i = 0; i < BULLET_CACHE_SIZE; ++i)
	{
		unuseBullets.push_back(new Bullet());
	}

	totalAmmo = 30;
	haveAmmo = totalAmmo;

	font.loadFromFile("fonts/zombiecontrol.ttf");
	textReloading.setString("RELOADING...");
	textReloading.setCharacterSize(15);
	textReloading.setFillColor(Color::Green);
	textReloading.setFont(font);
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
	ViewManager::GetInstance()->CameraShake(timeHit.asSeconds());
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
	Vector2f dir(h, v); 

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
	if (InputMgr::GetMouseButtonDown(Mouse::Button::Left) && !Reloading)
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
		if (timer < 0.f)
		{
			Reload();
			Reloading = false;
			timer = 2.f;
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

	ViewManager::GetInstance()->turnoffDimmed();
}

bool Player::UpdateCollision(const std::list<Pickup*> items)
{
	//아이템과 충돌처리로 습득
	FloatRect bounds = sprite.getGlobalBounds();
	bool isCollided = false;
	for (auto item : items)
	{
		if (bounds.intersects(item->GetGlobalBound()))
		{
			switch (item->GetType())
			{
			case PickupTypes::Ammo:
				if (item->GetIsGetIt())
				{
					haveAmmo += item->GotIt();
				}
				break;
			case PickupTypes::Health:
				if (item->GetIsGetIt())
				{
					health += item->GotIt();
				}
				break;
			default:
				break;
			}
		}
		isCollided = true;
	}
	return false;
}

bool Player::UpdateCollision(const std::vector<Zombie*>& zombies)
{
	//좀비와 총알 충돌
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

	// 재장전 UI
	if (Reloading)
	{
		textReloading.setPosition(position.x, position.y-30.f);
		Utils::SetOrigin(textReloading, Pivots::CT);
		window.draw(textReloading);
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
	health = maxHealth;
}

void Player::Reload()
{
	haveAmmo = totalAmmo + (RELOAD_AMMO * GameLevelData::GetInstance()->GetClipSize());
}

int Player::GetHaveAmmo()
{
	return haveAmmo;
}

void Player::SetHaveAmmo(int ammo)
{
	haveAmmo = ammo;
}

int Player::GetTotalAmmo()
{
	return totalAmmo;
}