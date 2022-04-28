#include <SFML/Graphics.hpp>
#include "utils/Utils.h"
#include "utils/InputMgr.h"
#include "utils/TextureHolder.h"
#include "utils/ViewManager.h"
#include "utils/SceneManager.h"
#include "sound/SoundManager.h"

using namespace std;
using namespace sf;

int main()
{
	/*********************************
	* Init
	**********************************/
	TextureHolder textureHolder;
	ViewManager::GetInstance()->Init();
	RenderWindow window(VideoMode(ViewManager::GetInstance()->GetResolution().x, ViewManager::GetInstance()->GetResolution().y)
		, "Zombie Arena!", Style::Fullscreen);

	SceneManager::GetInstance()->LoadScene(SCENE_TYPE::TITLE);
	InputMgr::Init();
	SoundManager::GetInstance()->Init();

	Clock clock;
	while (window.isOpen())
	{
		Time dt = clock.restart();
		/*********************************
		* Input
		**********************************/
		InputMgr::ClearInput();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			
			InputMgr::ProcessInput(event);
		}
		/*********************************
		* Esc
		**********************************/
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*********************************
		* Update
		**********************************/

		InputMgr::Update(dt.asSeconds(), window, ViewManager::GetInstance()->GetMainView());

		SceneManager::GetInstance()->UpdateScene(dt.asSeconds());

		/*********************************
		* Draw
		**********************************/ 
		window.clear();
		window.setView(ViewManager::GetInstance()->GetMainView());
		SceneManager::GetInstance()->DrawScene(window);
		//window.setView(ViewManager::GetInstance()->GetUiView());
		window.display();
	}

	ViewManager::GetInstance()->ClearView();
	SceneManager::GetInstance()->ClearScene();
	return 0;
}