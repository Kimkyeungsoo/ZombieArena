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

void GameLevelData::SetScore(int score)
{
    this->score = score;
}

void GameLevelData::SetHighScore(int highScore)
{
    this->highScore = highScore;
}
