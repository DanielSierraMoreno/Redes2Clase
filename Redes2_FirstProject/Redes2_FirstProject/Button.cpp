#include "Button.h"
#include <SFML/Graphics/Texture.hpp>
Button::Button(float x, float y, sf::Texture texture)
{
	this->setPosition(x, y);
	this->setTexture(texture);
}

bool Button::CheckBounds(unsigned int x, unsigned int y)
{
	return this->getGlobalBounds().contains(x, y);
}


float Button::GetMiddlePosX() const {
    return getPosition().x;
}

float Button::GetLeftPivotX() const
{
	return getPosition().x - getGlobalBounds().width / 2.0f;
}

float Button::GetMiddlePosY() const {
    return getPosition().y;
}

void Button::AddOnClickListener(const OnClick& callback) {
	// Set the onClick callback function
	onClick = callback;
}

void Button::CenterPivot()
{
	sf::FloatRect bounds = getLocalBounds();  // Get button's local bounds
	setOrigin(bounds.width / 2.0f, bounds.height / 2.0f); // Set origin to center
}

void Button::PivotCorner()
{
	sf::FloatRect bounds = getLocalBounds();
	setOrigin(bounds.width , bounds.height); 
}






