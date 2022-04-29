#pragma once
#include "SFML/Audio.hpp"

using namespace sf;

class SoundManager
{
private:
	SoundBuffer* hitBuffer;
	SoundBuffer* pickupBuffer;
	SoundBuffer* powerupBuffer;
	SoundBuffer* reloadBuffer;
	SoundBuffer* reloadFailedBuffer;
	SoundBuffer* shootBuffer;
	SoundBuffer* splatBuffer;

	SoundManager();
	~SoundManager();

	static SoundManager* instance;
public:
	static SoundManager* GetInstance();
	Sound* hitSound;
	Sound* pickupSound;
	Sound* powerupSound;
	Sound* reloadSound;
	Sound* reloadFailedSound;
	Sound* shootSound;
	Sound* splatSound;

	void Init();
};

