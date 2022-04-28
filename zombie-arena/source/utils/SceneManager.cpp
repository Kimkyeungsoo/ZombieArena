#include "SceneManager.h"
#include "../Scene/TitleScene.h"
#include "../Scene/PlayScene.h"
#include "../Scene/UpgradeScene.h"
#include "../Scene/GameOverScene.h"
#include "../utils/UIManager.h"
#include "../utils/ViewManager.h"

void SceneManager::LoadScene(SCENE_TYPE type)
{
	ClearScene();
	ViewManager::GetInstance()->Init();
	UIManager::GetInstance()->Init(type);

	currType = type;
	switch (currType)
	{
	case SCENE_TYPE::TITLE:
		scene = new TitleScene();
		break;
	case SCENE_TYPE::PLAY:
		scene = new PlayScene();
		break;
	case SCENE_TYPE::UPGRADE:
		scene = new UpgradeScene();
		break;
	case SCENE_TYPE::GAME_OVER:
		scene = new GameOverScene();
		break;
	case SCENE_TYPE::NONE:
		break;
	default:
		break;
	}

	InitScene();
}

void SceneManager::InitScene()
{
	scene->Init();
}

void SceneManager::UpdateScene(float dt)
{
	scene->Update(dt);
}

void SceneManager::DrawScene(RenderWindow& window)
{	
	scene->Draw(window);
	UIManager::GetInstance()->Draw(currType, window);
}

void SceneManager::ClearScene()
{
	if (nullptr != scene)
	{
		scene->Clear();
		delete scene;
		scene = nullptr;
	}

	ViewManager::GetInstance()->ClearView();
}
