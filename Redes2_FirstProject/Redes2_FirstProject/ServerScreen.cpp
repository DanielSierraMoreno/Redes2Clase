#include "ServerScreen.h"
#include "Text.h";
#include "lobby.h"

ServerScreen::ServerScreen(int W, int H, std::string name) : Screen(W, H, name)
{
	startServerButton = new Button(GetMiddleScreenX(), GetMiddleScreenY(), TextureManager::getInstance().buttonTexture, "Start Server",this,40);
    startServerButton->CenterPivot();
	startServerButton->setColor(sf::Color::Red);
	startServerButton->AddOnClickListener([this]() {
		StartServer();
	});




}

void ServerScreen::StartServer()
{
    startServerButton->setColor(sf::Color::Green);
    Lobby* chat = Lobby::Server(port);
}

void ServerScreen::StartClient()
{

}
        


