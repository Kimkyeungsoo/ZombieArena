#include "GameLevelData.h"

int GameLevelData::GetCountZombies()
{
    return countZombies;
}

int GameLevelData::GetWave()
{
    return wave;
}

int GameLevelData::GetScore()
{
    return score;
}

int GameLevelData::GetHighScore()
{
    return highScore;
}

int GameLevelData::GetClipSize()
{
    return level_ClipSize;
}

int GameLevelData::GetLevel_HP()
{
    return level_Health_Pickup;
}

int GameLevelData::GetLevel_AP()
{
    return level_Ammo_Pickup;
}

float GameLevelData::GetSpawnTime_HP()
{
    return spawnTime_HP;
}

float GameLevelData::GetSpawnTime_AP()
{
    return spawnTime_AP;
}

void GameLevelData::SetDefaultData()
{
    countZombies = 10;
    wave = 1;
    score = 0;
    level_ClipSize = 0;
    level_Zombie = 0;
}

void GameLevelData::LevelUpCountZombies()
{
    level_Zombie++;
    countZombies = 10 + level_Zombie * 5;
}

void GameLevelData::AddZombies(int count)
{
    countZombies += count;
}

void GameLevelData::AddWave()
{
    wave++;
}

void GameLevelData::AddScore(int value)
{
    this->score += value;
}

void GameLevelData::SetScore(int score)
{
    this->score = score;
}

void GameLevelData::SetHighScore(int highScore)
{
    this->highScore = highScore;
}

void GameLevelData::UpgradeClipSize()
{
    level_ClipSize++;
}

void GameLevelData::Upgrade_HP_level()
{
    spawnTime_HP++;
    level_Health_Pickup++;
}

void GameLevelData::Upgrade_AP_level()
{
    spawnTime_AP++;
    level_Ammo_Pickup++;
}
