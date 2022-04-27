#include "TitleScene.h"
#include "..\utils\TextureHolder.h"
#include "..\utils\InputMgr.h"
#include "..\utils\SceneManager.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	textureBackground = TextureHolder::GetTexture("graphics/background.png");
	spriteBackground.setTexture(textureBackground);
}

void TitleScene::Update(float dt)
{
	// Enter key input, change to playscene
	if (InputMgr::GetKeyDown(Keyboard::Enter))
	{
		SceneManager::GetInstance()->LoadScene(SCENE_TYPE::PLAY);
	}
}

void TitleScene::Draw(RenderWindow& window)
{
	window.draw(spriteBackground);
}

void TitleScene::Clear()
{
}
