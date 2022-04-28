#pragma once
#include "SFML/Graphics.hpp"
#include "SceneManager.h"
#include "Singleton.h"
#include <vector>

#define SIZE_OF_MAP 0
#define CLIP_SIZE 1
#define MAX_HEALTH 2
#define SPEED 3
#define HP_LEVEL 4
#define AP_LEVEL 5

using namespace sf;

class UIManager : public Singleton<UIManager>
{
private:
	Text textMessage;
	Text textHighScore;
	Font fontZombiecontrol;
	FloatRect textRect;

	Text textHighScoreNumber;
	Text textScore;
	Text textScoreNumber;
	Text textWave;
	Text textWaveNumber;
	Text textZombieCount;
	Text textZombieCountNumber;
	Text textHealth;
	Text textAmmo;
	Texture textureAmmoIcon;
	Sprite spriteAmmoIcon;

	std::vector<Text> textUpgrades;

	Text textGameOver;
	Text textRestart;

public:
	void SetTextRect(Text& text);

	void Init(SCENE_TYPE type);
	void Draw(SCENE_TYPE type, RenderWindow& window);

	void Init_TitleScene();
	void Draw_TitleScene(RenderWindow& window);

	void Init_PlayScene();
	void Draw_PlayScene(RenderWindow& window);
	void Update_PlayScene();

	void Init_UpgradeScene();
	void Draw_UpgradeScene(RenderWindow& window);
	void Update_UpgradeScene();

	void Init_GameOverScene();
	void Draw_GameOverScene(RenderWindow& window);
};

