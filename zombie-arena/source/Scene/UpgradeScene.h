#pragma once
#include "Scene.h"

class UpgradeScene : public Scene
{
private:
	Texture textureBackground;
	Sprite spriteBackground;

	bool isChooseUpgrade;

public:
	UpgradeScene();
	virtual ~UpgradeScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void Clear() override;
};

