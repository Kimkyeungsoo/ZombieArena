#include "SoundManager.h"

SoundManager* SoundManager::instance = nullptr;

SoundManager::~SoundManager()
{
	hitSound->stop();
	pickupSound->stop();
	powerupSound->stop();
	reloadSound->stop();
	reload_failedSound->stop();
	shootSound->stop();
	splatSound->stop();

	delete hitBuffer;
	delete hitSound;

	delete pickupBuffer;
	delete pickupSound;

	delete powerupBuffer;
	delete reloadBuffer;
	delete reload_failedBuffer;
	delete shootBuffer;
	delete splatBuffer;

	hitBuffer = nullptr;
	pickupBuffer = nullptr;
	powerupBuffer = nullptr;
	reloadBuffer = nullptr;
	reload_failedBuffer = nullptr;
	shootBuffer = nullptr;
	splatBuffer = nullptr;
}


SoundManager* SoundManager::GetInstance()
{
	if (nullptr == instance)
	{
		instance = new SoundManager();
	}
	return instance;
}

void SoundManager::Init()
{
	hitBuffer = new SoundBuffer;
	hitSound = new Sound;

	pickupBuffer = nullptr;
	powerupBuffer = nullptr;
	reloadBuffer = nullptr;
	reload_failedBuffer = nullptr;
	shootBuffer = nullptr;
	splatBuffer = nullptr;

}
