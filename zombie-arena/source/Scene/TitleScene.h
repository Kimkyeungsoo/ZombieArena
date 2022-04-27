#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
private:
	Texture textureBackground;
	Sprite spriteBackground;

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void Clear() override;
};

