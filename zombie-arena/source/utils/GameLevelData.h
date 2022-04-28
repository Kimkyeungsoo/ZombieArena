#pragma once
#include "Singleton.h"

class GameLevelData : public Singleton<GameLevelData>
{
private:
	int countZombies = 0;
	int wave = 0;
	int score = 0;
	int highScore = 0;
	int level_ClipSize = 0; //리로드 강화한 횟수
public:

	int GetCountZombies();
	int GetWave();
	int GetScore();
	int GetHighScore();
	int GetClipSize();

	void SetCountZombies(int count);
	void AddZombies(int count);
	void SetWave(int value);
	void AddScore(int value);
	void SetScore(int score);
	void SetHighScore(int highScore);
	void UpgradeClipSize();
};
