#include "UpgradeScene.h"
#include "../utils/TextureHolder.h"
#include "../utils/InputMgr.h"
#include "../utils/SceneManager.h"
#include "../utils/UIManager.h"

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
