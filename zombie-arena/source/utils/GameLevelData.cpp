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

void GameLevelData::SetCountZombies(int count)
{
    countZombies = count;
}

void GameLevelData::AddZombies(int count)
{
    countZombies += count;
}

void GameLevelData::SetWave(int value)
{
    wave = value;
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
