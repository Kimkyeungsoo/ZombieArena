#include "UpgradeScene.h"
#include "..\utils\TextureHolder.h"
#include "..\utils\InputMgr.h"
#include "..\utils\SceneManager.h"

UpgradeScene::UpgradeScene()
	:isChooseUpgrade(false)
{
}

UpgradeScene::~UpgradeScene()
{
}

void UpgradeScene::Init()
{
	textureBackground = TextureHolder::GetTexture("graphics/background.png");
	spriteBackground.setTexture(textureBackground);
}

void UpgradeScene::Update(float dt)
{
	// Choose upgrade one, go back playScene
	// ���⼭ ���׷��̵� �ߴ� ������ ���� playScene���� ����Ǿ� �ٲ��� ��
	// ��, player�� �޾ƿͼ� �������־�� ��
	// �׸��� clear �Ʊ� ������ ���⼭�� SceneManager�� �ٸ� ��������
	// ������ ���̵�(������ ������ �� �����Ŷ����..)�� ��������� �� �־�� ��
	// �׽�Ʈ�� �齺���̽� ����ȯ
	if (isChooseUpgrade || InputMgr::GetKeyDown(Keyboard::Backspace))
	{
		SceneManager::GetInstance()->LoadScene(SCENE_TYPE::PLAY);
	}

	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		SceneManager::GetInstance()->LoadScene(SCENE_TYPE::GAME_OVER);
	}
}

void UpgradeScene::Draw(RenderWindow& window)
{
	window.draw(spriteBackground);
}

void UpgradeScene::Clear()
{
}
