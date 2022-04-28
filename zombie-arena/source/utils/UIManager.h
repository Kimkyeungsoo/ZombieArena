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


	Text textScore;
	Text textZombieCount;
	Text textAmmo;
	Sprite spriteAmmoIcon;

	// ���� �� �ڵ忡�� list�� �������� vector�� ��������?
	
	// list�� ��� ������ �߿��ϸ� �߰� ��ġ�� �߰� ������ �� �ÿ� �����ϰ�
	// ������ �޸� ������ ������ �ʾƵ� �Ǳ� ������ ���ϴ�.
	// push_back�� ��� �߰��� ������ �Ź� �Ҵ��ϱ⿡ vector���� ������.

	// vector�� ��� ������ ����� ���� ���������� �߰� ������ �� ��� ����
	// ������ clear�� �ϴ��� �޸� ������ ���־�� ������
	// push_back�� ��� �̸� ���� ���� �Ҵ��ϰ� ����ϱ� ������ 
	// �޸������� ������ �� �ִ�. ��, insert�� ��� �Ҹ�

	// ȭ�鿡 �׷��ִ� UI�̸� ������ �߰������� �Ͼ�� �ʱ� ������
	// �� ��� vector�� �������� ������?
	std::vector<Text> textUpgrades;
	

public:
	void SetTextRect(Text& text);

	void Init(SCENE_TYPE type);
	void Draw(SCENE_TYPE type, RenderWindow& window);

	void Init_TitleScene();
	void Draw_TitleScene(RenderWindow& window);

	void Init_PlayScene();
	void Draw_PlayScene(RenderWindow& window);

	void Init_UpgradeScene();
	void Draw_UpgradeScene(RenderWindow& window);
};

