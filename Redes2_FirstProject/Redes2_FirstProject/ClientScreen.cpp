#include "ClientScreen.h"
#include "Utils.h"
#include "lobby.h"
#include "RoomSelectionScreen.h"
#include "ScreenManager.h"
ClientScreen::ClientScreen(int W, int H, std::string name) : Screen(W, H, name,true)
{
	visible = true;
	userNameInput = new InputText(200, 50, "Insert name: ", this,10);
	userNameInput->AddDraweable();
	userNameInput->StartTyping();

	ipInput = new InputText(200, 150, "Insert IP: ", this,15);
	ipInput->AddDraweable();
	ipInput->stringContent = "192.168.1.144";
	portInput = new InputText(200, 200, "Insert PORT: ", this,5);
	portInput->AddDraweable();
	portInput->stringContent = "3001";
	Button* startButton = new Button(W - 50, H - 25, TextureManager::getInstance().buttonTexture, "Connect",this,20);
	startButton->CenterPivot();

	startButton->setScale(0.35, 0.2);
	startButton->setColor(sf::Color::Red);
	startButton->AddOnClickListener([this]() {
		ConnectToServer();
		});
}

void ClientScreen::ConnectToServer()
{
	userName = userNameInput->stringContent;
	ip = ipInput->stringContent;
	port = std::stoi(portInput->stringContent);

	Lobby* client = Lobby::Client(userName,ip,port);


	RoomSelectionScreen* screen = new RoomSelectionScreen(800, 600, "Lobby");
	ScreenManager::getInstance().AddScreen(screen);

	screen->SetData(client);


}
