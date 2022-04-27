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
public:
	void Init();
	void ClearView();
	View& GetMainView();
	View& GetUiView();
	Vector2i& GetResolution();
};

