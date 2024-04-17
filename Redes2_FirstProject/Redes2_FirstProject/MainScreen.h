#pragma once
#include "Screen.h"
#include "Button.h"
#include "SFML/Network.hpp"
#include "SocketsManager.h"


class MainScreen : public Screen
{
public:

	MainScreen(int W, int H, std::string name);
	void OpenServerScreen();
	void OpenClientScreen();
private:
	Button* startServerButton;
	Button* startClientButton;
};
