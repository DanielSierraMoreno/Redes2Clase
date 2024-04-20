#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "TextureManager.h";
#include "Button.h"
#include "InputText.h"

class Screen
{
private:
	int WIDTH;
	int HEIGTH;
	std::vector<Button*> buttons;
	std::vector<sf::Drawable*> drawables;
	sf::RenderWindow window;
	int scroll;
public:
	InputText* selectedInputText;
	Screen(int W, int H, std::string name);


	void AddDraweable(sf::Drawable* draweable);
	virtual void Update();
	void Draw();
	void Events();
	virtual void MouseButtonPressedEvents(sf::Event event);
	virtual void MouseButtonRelesedEvents(sf::Event event);
	virtual void KeyPressedEvents(sf::Event event);
	float GetMiddleScreenX();
	float GetMiddleScreenY();
	bool isOpen();
	int GetScroll();
	void ResetScroll();
	void RemoveDrawable(sf::Drawable* drawableToRemove);
};

