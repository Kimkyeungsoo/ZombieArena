#pragma once
#include "Singleton.h"

class GameLevelData : public Singleton<GameLevelData>
{
private:
	int countZombies = 10;
	int wave = 1;
	int score = 0;
	int highScore = 0;
	int level_ClipSize = 0; //리로드 강화한 횟수
	int level_Zombie = 0;
	int level_Health_Pickup = 1;
	float spawnTime_HP = 0;
	int level_Ammo_Pickup = 1;
	float spawnTime_AP = 0;
public:

	int GetCountZombies();
	int GetWave();
	int GetScore();
	int GetHighScore();
	int GetClipSize();
	int GetLevel_HP();
	int GetLevel_AP();
	float GetSpawnTime_HP();
	float GetSpawnTime_AP();

	void SetDefaultData();

	void AddZombies(int count);
	void AddWave();
	void AddScore(int value);
	void SetScore(int score);
	void SetHighScore(int highScore);

	void LevelUpCountZombies();

	void UpgradeClipSize();
	void Upgrade_HP_level();
	void Upgrade_AP_level();
};
