#pragma once
#include <SFML/Audio.hpp>

using namespace sf;

class SoundManager
{
	SoundBuffer* hitBuffer;
	SoundBuffer* pickupBuffer;
	SoundBuffer* powerupBuffer;
	SoundBuffer* reloadBuffer;
	SoundBuffer* reload_failedBuffer;
	SoundBuffer* shootBuffer;
	SoundBuffer* splatBuffer;

	SoundManager()
		:hitBuffer(nullptr),pickupBuffer(nullptr),powerupBuffer(nullptr),reloadBuffer(nullptr),
		reload_failedBuffer(nullptr),shootBuffer(nullptr),splatBuffer(nullptr){}

	~SoundManager();

	static SoundManager* instance;
public:
	static SoundManager* GetInstance();
	Sound* hitSound;
	Sound* pickupSound;
	Sound* powerupSound;
	Sound* reloadSound;
	Sound* reload_failedSound;
	Sound* shootSound;
	Sound* splatSound;

	void Init();
};

