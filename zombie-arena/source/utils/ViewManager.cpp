#include "ViewManager.h"
#include "Utils.h"

void ViewManager::Init()
{
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	mainView = new View(FloatRect(0.f, 0.f, resolution.x, resolution.y));
	uiView = new View(FloatRect(0.f, 0.f, resolution.x, resolution.y));
}

void ViewManager::ClearView()
{
	delete mainView;
	mainView = nullptr;

	delete uiView;
	uiView = nullptr;
}

View& ViewManager::GetMainView()
{
	return *mainView;
}

void ViewManager::CameraShake(float dt)
{
	while (shakeTime > 0)
	{
		mainView->move(Utils::Random(-3.f, 3.f), Utils::Random(-3.f, 3.f));
		shakeTime -= dt;
	}
	shakeTime = 2.f;
}

View& ViewManager::GetUiView()
{
	return *uiView;
}

Vector2i& ViewManager::GetResolution()
{
	return resolution;
}
