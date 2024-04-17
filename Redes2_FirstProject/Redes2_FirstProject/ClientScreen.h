#pragma once
#pragma once
#include "Screen.h"
#include "Button.h"
#include "SFML/Network.hpp"
#include "SocketsManager.h"
#include "Text.h"


class ClientScreen : public Screen
{
public:
	ClientScreen(int W, int H, std::string name);
	std::string userName;
	std::string ip;
	int port;
	InputText* userNameInput;
	InputText* ipInput;
	InputText* portInput;

private:
	void ConnectToServer();
};

