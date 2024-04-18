#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "Text.h";

class Screen;

class Button: public sf::Sprite
{
public:

	typedef std::function<void()> OnClick;
	OnClick onClick = []() {};
	Button();
	Button(float x, float y,sf::Texture texture, std::string textName, Screen* currentScrren, int fontSize);
	Button(float x, float y, sf::Texture texture);

	bool CheckBounds(unsigned int x, unsigned int y);
	float GetMiddlePosX() const;
	float GetLeftPivotX() const;
	float GetMiddlePosY() const;
	void AddOnClickListener(const OnClick& callback);
	void CenterPivot();
	void PivotCorner();
	void UpdatePosition(int x);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	Text* name;

};

