#pragma once
#include "Screen.h"
#include "Button.h"
#include "SFML/Network.hpp"
#include "SocketsManager.h"

enum PackagesIds : Packet::PacketKey { Message = 0 };

class ServerScreen : public Screen
{
public:
	ServerScreen(int W, int H, std::string name);
	void StartServer();
	void StartClient();
private:
	unsigned short port = 3001;
	Button* startServerButton;
};

