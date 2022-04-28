#pragma once
#include "Scene.h"

class GameOverScene : public Scene
{
public:
	GameOverScene();
	virtual ~GameOverScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void Clear() override;
};

