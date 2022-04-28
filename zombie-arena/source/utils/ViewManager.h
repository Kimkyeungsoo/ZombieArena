#pragma once
#include "Singleton.h"
#include "SFML/Graphics.hpp"

using namespace sf;

class ViewManager : public Singleton<ViewManager>
{
private:
	View* mainView = nullptr;
	View* uiView = nullptr;
	Vector2i resolution;
	float shakeTime = 2.f;
public:
	void Init();
	void ClearView();
	void CameraShake(float dt);
	View& GetMainView();
	View& GetUiView();
	Vector2i& GetResolution();
};

