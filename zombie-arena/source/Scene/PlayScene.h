#pragma once
#include "Scene.h"
#include "..\plyer\Player.h"
#include <list>
#include <vector>

class Pickup;
class Zombie;
class PlayScene : public Scene
{
private:
	IntRect arena;
	std::list<Pickup*> items;
	Player player;
	std::vector<Zombie*> zombies;

	Texture textureBackground;
	VertexArray tileMap;

	Texture textureCrosshair;
	Sprite spriteCrosshair;

	int countZombies;
	Time playTime;
	Clock clock;

public:
	PlayScene();
	virtual ~PlayScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void Clear() override;
	
	void SetArenaSize(int x, int y);
	void AddItems();
	int CreateBackground(VertexArray& va, IntRect arena);
	void CreateZombies(std::vector<Zombie*>& zombies, int count, IntRect arena);
	void CollisionCheck();
};

