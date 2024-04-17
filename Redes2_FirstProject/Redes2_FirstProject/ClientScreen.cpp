#include "ClientScreen.h"
#include "Utils.h"
#include "Chat.h"
#include "RoomSelectionScreen.h"
#include "ScreenManager.h"
ClientScreen::ClientScreen(int W, int H, std::string name) : Screen(W, H, name)
{
	userNameInput = new InputText(200, 50, "Insert name: ", this);
	userNameInput->AddDraweable();
	userNameInput->StartTyping();

	ipInput = new InputText(200, 150, "Insert IP: ", this);
	ipInput->AddDraweable();

	portInput = new InputText(200, 200, "Insert PORT: ", this);
	portInput->AddDraweable();

	Button* startButton = new Button(W - 5, H - 5, TextureManager::getInstance().buttonTexture);
	startButton->PivotCorner();
	startButton->setScale(0.35, 0.2);
	startButton->setColor(sf::Color::Red);
	startButton->AddOnClickListener([this]() {
		ConnectToServer();
		});
	AddDraweable(startButton);

	Text* textb = new Text(startButton->GetMiddlePosX() - 38, startButton->GetMiddlePosY() - 25, "Connect", 20);
	textb->CenterText();
	AddDraweable(&textb->text);
}

void ClientScreen::ConnectToServer()
{
	userName = userNameInput->stringContent;
	ip = ipInput->stringContent;
	port = std::stoi(portInput->stringContent);

	Lobby* client = Lobby::Client(ip,port);
	RoomSelectionScreen* screen = new RoomSelectionScreen(800, 600, "Lobby");
	ScreenManager::getInstance().AddScreen(screen);

	screen->SetData(client);


}
