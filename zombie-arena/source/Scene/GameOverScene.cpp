#include "GameOverScene.h"
#include "../utils/InputMgr.h"
#include "../utils/TextureHolder.h"
#include "../utils/SceneManager.h"
#include "../plyer/Player.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Init()
{
	textureBackground = TextureHolder::GetTexture("graphics/background_originalsize.png");
	spriteBackground.setTexture(textureBackground);

	spriteBackground.setPosition(1920.f * 0.5f - textureBackground.getSize().x * 0.5f
		, 1080 * 0.5f - textureBackground.getSize().y * 0.5f);
}

void GameOverScene::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Enter))
	{
		Player::GetInstance()->DestroyInstance();
		SceneManager::GetInstance()->LoadScene(SCENE_TYPE::TITLE);
	}
}

void GameOverScene::Draw(RenderWindow& window)
{
	window.draw(spriteBackground);
}

void GameOverScene::Clear()
{
}
