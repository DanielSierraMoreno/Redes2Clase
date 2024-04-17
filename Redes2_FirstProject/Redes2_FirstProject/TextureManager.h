#pragma once
#include <SFML/Graphics/Texture.hpp>

class TextureManager
{
public:
	TextureManager();
	sf::Texture buttonTexture;
	void LoadTextures();

	static TextureManager& getInstance();
};

