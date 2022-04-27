#pragma once
// 해야 할 일 Texture를 들고있다가 Sprite를 생성할 때 사용
// Single 턴으로 사용
#include "SFML/Graphics.hpp"
#include <map>

using namespace sf;
using namespace std;

class TextureHolder
{
private:
	map<string, Texture> mapTexture;

	static TextureHolder* instance;
public:
	TextureHolder();

	static Texture& GetTexture(string filename);
};

