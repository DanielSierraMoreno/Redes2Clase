#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
class Button: public sf::Sprite
{
public:

	typedef std::function<void()> OnClick;
	OnClick onClick = []() {};

	Button(float x, float y,sf::Texture texture);

	bool CheckBounds(unsigned int x, unsigned int y);
	float GetMiddlePosX() const;
	float GetLeftPivotX() const;
	float GetMiddlePosY() const;
	void AddOnClickListener(const OnClick& callback);
	void CenterPivot();
	void PivotCorner();
private:
	sf::Texture texture;
	sf::Sprite sprite;
};

