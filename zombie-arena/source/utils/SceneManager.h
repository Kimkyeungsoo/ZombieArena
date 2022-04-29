#pragma once
#include "Singleton.h"
#include "../Scene/Scene.h"

enum class SCENE_TYPE
{
	TITLE,
	PLAY,
	UPGRADE,
	GAME_OVER,
	NONE,
};

class SceneManager : public Singleton<SceneManager>
{
private:
	Scene* scene = nullptr;
	SCENE_TYPE currType = SCENE_TYPE::NONE;
public:
	void LoadScene(SCENE_TYPE type);
	void InitScene();
	void UpdateScene(float dt);
	void DrawScene(RenderWindow& window);
	void ClearScene();
};

