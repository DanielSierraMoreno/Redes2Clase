#include "TextureManager.h"
#include <stdexcept>
#include <string>

TextureManager::TextureManager()
{
	LoadTextures();
}

void TextureManager::LoadTextures()
{
	if (!buttonTexture.loadFromFile("resources/button.png"))
	{
		throw std::runtime_error("Error loading texture from file: resources/button.png");
	}
}

TextureManager& TextureManager::getInstance() {
	static TextureManager instance;
	return instance;
}
