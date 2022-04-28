#include "PlayScene.h"
#include "..\utils\Utils.h"
#include "..\utils\TextureHolder.h"
#include "..\zombie\Zombie.h"
#include "..\utils\Pickup.h"
#include "..\utils\ViewManager.h"
#include "..\utils\InputMgr.h"
#include "..\utils\SceneManager.h"
#include "..\utils\ViewManager.h"
#include "..\plyer\Player.h"
#include "..\utils\UIManager.h"

PlayScene::PlayScene()
	:countZombies(10)
{
	textureBackground = TextureHolder::GetTexture("graphics/background_sheet.png");
	textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	Utils::SetOrigin(spriteCrosshair, Pivots::CC);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	SetArenaSize(800, 800);
	AddItems();

	Player::GetInstance()->Spawn(arena, ViewManager::GetInstance()->GetResolution(), 0);
	Player::GetInstance()->SetHaveAmmo(Player::GetInstance()->GetTotalAmmo());
	CreateZombies(zombies, countZombies, arena);
	CreateBackground(tileMap, arena);
}

void PlayScene::Update(float dt)
{
	// playTime은 Time형 dt는 float형이라 일단 임시
	playTime += clock.restart();
	
	for (auto zombie : zombies)
	{
		zombie->Update(dt, Player::GetInstance()->GetPosition(), arena);
	}

	for (auto item : items)
	{
		item->Update(dt);
	}

	Player::GetInstance()->Update(dt, arena);
	spriteCrosshair.setPosition(InputMgr::GetMouseWorldPosition());
	ViewManager::GetInstance()->GetMainView().setCenter(Player::GetInstance()->GetPosition());
	
	CollisionCheck();

	UIManager::GetInstance()->Update_PlayScene();

	// 씬넘어가기 위한 테스트용
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		SceneManager::GetInstance()->LoadScene(SCENE_TYPE::UPGRADE);
	}
}

void PlayScene::Draw(RenderWindow& window)
{
	window.draw(tileMap, &textureBackground);

	for (auto zombie : zombies)
	{
		if (!zombie->IsAlive() && zombie->IsTime())
		{
		window.draw(zombie->GetBlood().GetSprite());
		}
	}

	for (auto item : items)
	{
		window.draw(item->GetSprite());
	}

	for (auto zombie : zombies)
	{
		if (zombie->IsAlive())
		{
			window.draw(zombie->GetSprite());
		}
	}

	Player::GetInstance()->Draw(window);

	window.draw(spriteCrosshair);
}

void PlayScene::Clear()
{
	// 동적할당 해놨던 pickup들 정리
	for (auto it : items)
	{
		delete it;
		it = nullptr;
	}
	items.clear();

	// 동적할당 해놨던 zombie들 정리
	for (auto zombie : zombies)
	{
		delete zombie;
		zombie = nullptr;
	}
	zombies.clear();
}

int PlayScene::CreateBackground(VertexArray& va, IntRect arena)
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

void PlayScene::CreateZombies(std::vector<Zombie*>& zombies, int count, IntRect arena)
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

void PlayScene::SetArenaSize(int x, int y)
{
	arena.width = x;
	arena.height = y;
}

void PlayScene::CollisionCheck()
{
	Player::GetInstance()->UpdateCollision(zombies);

	for (auto zombie : zombies)
	{
		if (zombie->UpdateCollision(playTime, *Player::GetInstance()))
		{
			break;
		}
	}

	Player::GetInstance()->UpdateCollision(items);
}

void PlayScene::AddItems()
{
	// 여기서 새로 동적할당을 매번하고,
	// items에 넣어주는 식으로 간다면
	// 이 함수가 호출될 때마다 아이템이 추가로 배치될 수 있음
	Pickup* ammoPickup = new Pickup(PickupTypes::Ammo);
	Pickup* healthPickup = new Pickup(PickupTypes::Health);

	ammoPickup->SetArena(arena);
	healthPickup->SetArena(arena);

	items.push_back(ammoPickup);
	items.push_back(healthPickup);
}
