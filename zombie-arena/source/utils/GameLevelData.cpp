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
