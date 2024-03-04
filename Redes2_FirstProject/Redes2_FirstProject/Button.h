#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Button: public sf::Sprite
{
public:

	typedef std::function<void()> OnClick;
	OnClick onClick = [](){};


private:



};

