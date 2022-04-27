#include <SFML/Graphics.hpp>
#include "utils/Utils.h"
#include "utils/InputMgr.h"
#include "plyer/Player.h"
#include <iostream>
#include "utils/TextureHolder.h"
#include "zombie/Zombie.h"
#include "bullet/Bullet.h"
#include "utils/Pickup.h"

using namespace std;
using namespace sf;

int CreateBackground(VertexArray& va, IntRect arena)    // 버텍스어레이와 렉사이즈
{

	const int TILE_SIZE = 50;
	const int TIMLE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;

	int cols = arena.width / TILE_SIZE;
	int rows = arena.height / TILE_SIZE;

	va.setPrimitiveType(Quads);
	va.resize(cols * rows * VERTS_IN_QUAD);

	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c)
		{
			int index = r * cols + c;

			float x = c * TILE_SIZE;
			float y = r * TILE_SIZE;			
			int vertexIndex = index * VERTS_IN_QUAD;

			va[vertexIndex + 0].position = Vector2f(x, y);
			va[vertexIndex + 1].position = Vector2f(x + TILE_SIZE, y);
			va[vertexIndex + 2].position = Vector2f(x + TILE_SIZE, y + TILE_SIZE);
			va[vertexIndex + 3].position = Vector2f(x, y + TILE_SIZE);

			int texIndex = index % 4;
			float offset = texIndex * TILE_SIZE;
			if (r == 0 || c == 0 || r == rows - 1 || c == cols - 1)
			{
				offset = TILE_SIZE * 3;
			}
			else
			{
				offset = TILE_SIZE * Utils::Random(0, TIMLE_TYPES);
			}
			va[vertexIndex + 0].texCoords = Vector2f(0.f, offset);
			va[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE, offset);
			va[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE, offset + TILE_SIZE);
			va[vertexIndex + 3].texCoords = Vector2f(0.f, offset + TILE_SIZE);
		}
	}
	return 0;
}

void CreateZombies(std::vector<Zombie*>& zombies, int count, IntRect arena)	// 좀비 수, 생성 영역
{
	for (auto v : zombies)
	{
		delete v;
	}

	zombies.clear();

	int offeset = 50;
	int minX = arena.left + offeset;
	int maxX = arena.width - offeset;
	int minY = arena.top + offeset;
	int maxY = arena.height - offeset;
	/*********************************
	* 플레이어 주변 좀비 생성 X
	*********************************/
	int distance = 200;
	int centerX = (arena.width - arena.left) / 2;
	int centerY = (arena.height - arena.top) / 2;

	for (int i = 0; i < count; ++i)
	{
		int x = Utils::Random(minX, maxX + 1);
		int y = Utils::Random(minY, maxY + 1);
		/*********************************
		* 플레이어 주변 좀비 생성 X
		*********************************/
		while ((x > centerX - distance && x < centerX + distance) &&
			(y > centerY - distance && y < centerY + distance))
		{
			x = Utils::Random(minX, maxX + 1);
			y = Utils::Random(minY, maxY + 1);
		}

		ZombieTypes type = (ZombieTypes)Utils::Random(0, (int)ZombieTypes::COUNT);

		Zombie* zombie = new Zombie();
		zombie->Spawn(x, y, type);

		zombies.push_back(zombie);
	}	
}

int main()
{
	TextureHolder textureHolder;

	Vector2i resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena!", Style::Fullscreen);

	window.setMouseCursorVisible(false);	// 마우스 커서 숨김
	/***************************************
	* 크로스헤어
	****************************************/
	Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	Sprite spriteCrosshair;
	spriteCrosshair.setTexture(textureCrosshair);
	Utils::SetOrigin(spriteCrosshair, Pivots::CC);
	
	View mainView(FloatRect(0.f, 0.f, resolution.x, resolution.y));

	View uiView(FloatRect(0.f, 0.f, resolution.x, resolution.y));

	InputMgr::Init();

	IntRect arena;
	//arena.width = resolution.x;
	//arena.height = resolution.y;
	arena.width = 800;
	arena.height = 800;

	Pickup ammoPickup(PickupTypes::Ammo);
	Pickup healthPickup(PickupTypes::Health);
	ammoPickup.SetArena(arena);
	healthPickup.SetArena(arena);

	std::list<Pickup*> items;
	items.push_back(&ammoPickup);
	items.push_back(&healthPickup);

	Player player;
	player.Spawn(arena, resolution, 0.f);

	std::vector<Zombie*> zombies;
	CreateZombies(zombies, 30, arena);

	Clock clock;
	Time playTime;

	Texture& texBackground = TextureHolder::GetTexture("graphics/background_sheet.png");
	//texBackground.loadFromFile("graphics/background_sheet.png");

	VertexArray tileMap;
	CreateBackground(tileMap, arena);
	while (window.isOpen())
	{
		Time dt = clock.restart();
		playTime += dt;
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
		InputMgr::Update(dt.asSeconds(), window, mainView);

		for (auto zombie : zombies)
		{
			zombie->Update(dt.asSeconds(), player.GetPosition(), arena);
		}

		ammoPickup.Update(dt.asSeconds());
		healthPickup.Update(dt.asSeconds());
		//cout << InputMgr::GetAxis(Axis::Horizontal) << endl;    // 테스트
		spriteCrosshair.setPosition(InputMgr::GetMouseWorldPosition());
		player.Update(dt.asSeconds(), arena);

		mainView.setCenter(player.GetPosition());

		/*********************************
		* 충돌 체크
		**********************************/
		player.UpdateCollision(zombies);
		for (auto zombie : zombies)
		{
			if (zombie->UpdateCollision(playTime, player))
			{
				break;
			}
		}
		player.UpdateCollision(items);	// 아이템 충돌
		/*********************************
		* Draw
		**********************************/ 
		window.clear();
		window.setView(mainView);	// 월드 기준 포지션
		window.draw(tileMap, &texBackground);

		if (ammoPickup.IsSpawned())
		{
			window.draw(ammoPickup.GetSprite());
		}
		if (healthPickup.IsSpawned())
		{
			window.draw(healthPickup.GetSprite());
		}

		for (auto zombie : zombies)
		{
			window.draw(zombie->GetSprite());
		}
		//window.draw(player.GetSprite());
		player.Draw(window);

		window.draw(spriteCrosshair);

		window.setView(uiView);	// 화면 좌표계 기준
		// UI
		window.display();
	}

	return 0;
}