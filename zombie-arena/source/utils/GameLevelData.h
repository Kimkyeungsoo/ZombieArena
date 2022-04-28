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
public:

	int GetCountZombies();
	int GetWave();
	int GetScore();
	int GetHighScore();
	int GetClipSize();

	void SetDefaultData();

	void AddZombies(int count);
	void AddWave();
	void AddScore(int value);
	void SetScore(int score);
	void SetHighScore(int highScore);

	void LevelUpCountZombies();

	void UpgradeClipSize();
};
