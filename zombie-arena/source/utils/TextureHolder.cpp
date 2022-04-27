#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(instance == nullptr);
	instance = this;
}

Texture& TextureHolder::GetTexture(string filename)
{
	// 1. filename key map에 있냐 없냐?
	// 2-1. 있을 때(map에서 찾아서 반환)
	// 2-2. 없을 때(만들어서 map에다가 insert)
	auto& map = instance->mapTexture;

	auto it = map.find(filename);
	if (it == map.end())
	{
		auto& texture = map[filename];
		texture.loadFromFile(filename);
	}
	return map[filename];
}
