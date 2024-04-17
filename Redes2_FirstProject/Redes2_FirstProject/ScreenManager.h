#pragma once
#include "Screen.h"
class ScreenManager
{
public:
	ScreenManager();
	std::vector<Screen*> screens;
	void AddScreen(Screen* screen);
	void UpdateAllScreens();

	static ScreenManager& getInstance();
};

