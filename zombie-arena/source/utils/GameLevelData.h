#pragma once
#include "Singleton.h"

// 게임에서 사용될 전역 데이터 관리

class GameLevelData : public Singleton<GameLevelData>
{
private:
	int countZombies = 10;			// 웨이브의 좀비 수
	int wave = 1;					// 웨이브 수
	int score = 0;					// 현재 점수
	int highScore = 0;				// 최고 점수

	int arena_x = 600;				// 타일 맵의 x크기
	int arena_y = 600;				// 타일 맵의 y크기

	int level_ClipSize = 0;			// 탄창 업그레이드 레벨
	int level_Zombie = 0;			// 좀비 수 업그레이드 레벨
	int level_Health_Pickup = 1;	// 힐링팩 갯수 업그레이드 레벨
	int level_Ammo_Pickup = 1;		// 탄창 갯수 업그레이드 레벨
	float spawnTime_HP = 0;			// 힐링팩 스폰 시간 줄여주는 레벨
	float spawnTime_AP = 0;			// 탄창 스폰 시간 줄여주는 레벨
public:

	int GetCountZombies();
	int GetWave();
	int GetScore();
	int GetHighScore();

	int GetArena_x();
	int GetArena_y();
	int GetClipSize();
	int GetLevel_HP();
	int GetLevel_AP();
	float GetSpawnTime_HP();
	float GetSpawnTime_AP();


	void AddZombies(int count);
	void AddWave();
	void AddScore(int value);

	void SetDefaultData();
	void SetScore(int score);
	void SetHighScore(int highScore);

	void LevelUpCountZombies();

	void UpgradeMapSize();
	void UpgradeClipSize();
	void Upgrade_HP_level();
	void Upgrade_AP_level();
};
