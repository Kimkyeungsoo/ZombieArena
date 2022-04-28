#pragma once
#include "SFML/Graphics.hpp"
#include "SceneManager.h"
#include "Singleton.h"
#include <vector>

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
	Text textZombieCount;
	Text textAmmo;
	Sprite spriteAmmoIcon;

	// 지금 내 코드에서 list가 유리한지 vector가 유리한지?
	
	// list의 경우 순서가 중요하며 중간 위치에 추가 삭제가 될 시에 유리하고
	// 별도의 메모리 관리를 해주지 않아도 되기 때문에 편하다.
	// push_back의 경우 추가될 때마다 매번 할당하기에 vector보다 느리다.

	// vector의 경우 순서와 상관은 없고 순차적으로 추가 삭제만 할 경우 유리
	// 별도로 clear를 하더라도 메모리 관리를 해주어야 하지만
	// push_back의 경우 미리 범위 값을 할당하고 사용하기 때문에 
	// 메모리적으로 유리할 수 있다. 단, insert의 경우 불리

	// 화면에 그려주는 UI이며 별도로 추가삭제가 일어나지 않기 때문에
	// 이 경우 vector가 유리하지 않을까?
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

