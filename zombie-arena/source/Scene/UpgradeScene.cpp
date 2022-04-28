#include "UpgradeScene.h"
#include "..\utils\TextureHolder.h"
#include "..\utils\InputMgr.h"
#include "..\utils\SceneManager.h"
#include "..\utils\UIManager.h"

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
	// 여기서 업그레이드 했던 정보를 토대로 playScene에서 적용되어 바뀌어야 함
	// 즉, player를 받아와서 변경해주어야 함
	// 그리고 clear 됐기 때문에 여기서든 SceneManager든 다른 곳에서든
	// 게임의 난이도(나오는 좀비의 수 같은거라던지..)를 변경시켜줄 수 있어야 함
	// 테스트용 백스페이스 씬전환
	if (isChooseUpgrade || InputMgr::GetKeyDown(Keyboard::Backspace))
	{
		SceneManager::GetInstance()->LoadScene(SCENE_TYPE::PLAY);
	}

	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		SceneManager::GetInstance()->LoadScene(SCENE_TYPE::GAME_OVER);
	}

	UIManager::GetInstance()->Update_UpgradeScene();
}

void UpgradeScene::Draw(RenderWindow& window)
{
	window.draw(spriteBackground);
}

void UpgradeScene::Clear()
{
}
