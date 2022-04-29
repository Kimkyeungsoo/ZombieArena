#include "SoundManager.h"

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager()
	: hitBuffer(nullptr), pickupBuffer(nullptr), powerupBuffer(nullptr), reloadBuffer(nullptr), reloadFailedBuffer(nullptr), shootBuffer(nullptr), splatBuffer(nullptr), hitSound(nullptr), pickupSound(nullptr), powerupSound(nullptr), reloadSound(nullptr), reloadFailedSound(nullptr), shootSound(nullptr), splatSound(nullptr)
{
}

SoundManager::~SoundManager()
{
	hitSound->stop();
	pickupSound->stop();
	powerupSound->stop();
	reloadSound->stop();
	reloadFailedSound->stop();
	shootSound->stop();
	splatSound->stop();

	delete hitBuffer;
	delete hitSound;
	delete pickupBuffer;
	delete pickupSound;
	delete powerupBuffer;
	delete powerupSound;
	delete reloadBuffer;
	delete reloadSound;
	delete reloadFailedBuffer;
	delete reloadFailedSound;
	delete shootBuffer;
	delete shootSound;
	delete splatBuffer;
	delete splatSound;

	hitBuffer = nullptr;
	hitSound = nullptr;
	pickupBuffer = nullptr;
	pickupSound = nullptr;
	powerupBuffer = nullptr;
	powerupSound = nullptr;
	reloadBuffer = nullptr;
	reloadSound = nullptr;
	reloadFailedBuffer = nullptr;
	reloadFailedSound = nullptr;
	shootBuffer = nullptr;
	shootSound = nullptr;
	splatBuffer = nullptr;
	splatSound = nullptr;
}

SoundManager* SoundManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new SoundManager();
	}
	return instance;
}

void SoundManager::Init()
{
	hitBuffer = new SoundBuffer;
	hitSound = new Sound;
	hitBuffer->loadFromFile("sound/hit.wav");
	hitSound->setBuffer(*hitBuffer);

	pickupBuffer = new SoundBuffer;
	pickupSound = new Sound;
	pickupBuffer->loadFromFile("sound/pickup.wav");
	pickupSound->setBuffer(*pickupBuffer);

	powerupBuffer = new SoundBuffer;
	powerupSound = new Sound;
	powerupBuffer->loadFromFile("sound/powerup.wav");
	powerupSound->setBuffer(*powerupBuffer);

	reloadBuffer = new SoundBuffer;
	reloadSound = new Sound;
	reloadBuffer->loadFromFile("sound/reload.wav");
	reloadSound->setBuffer(*reloadBuffer);

	reloadFailedBuffer = new SoundBuffer;
	reloadFailedSound = new Sound;
	reloadFailedBuffer->loadFromFile("sound/reload_failed.wav");
	reloadFailedSound->setBuffer(*reloadFailedBuffer);

	shootBuffer = new SoundBuffer;
	shootSound = new Sound;
	shootBuffer->loadFromFile("sound/shoot.wav");
	shootSound->setBuffer(*shootBuffer);

	splatBuffer = new SoundBuffer;
	splatSound = new Sound;
	splatBuffer->loadFromFile("sound/splat.wav");
	splatSound->setBuffer(*splatBuffer);
}
