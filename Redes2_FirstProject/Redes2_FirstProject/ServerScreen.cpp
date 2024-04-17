#include "ServerScreen.h"
#include "Text.h";
#include "Chat.h"

ServerScreen::ServerScreen(int W, int H, std::string name) : Screen(W, H, name)
{
	startServerButton = new Button(GetMiddleScreenX(), GetMiddleScreenY(), TextureManager::getInstance().buttonTexture);
    startServerButton->CenterPivot();
	startServerButton->setColor(sf::Color::Red);
	startServerButton->AddOnClickListener([this]() {
		StartServer();
	});
	AddDraweable(startServerButton);

	Text* text = new Text(startServerButton->GetMiddlePosX(),startServerButton->GetMiddlePosY(), "Start Server", 30);
	text->CenterText();
	AddDraweable(&text->text);


}

void ServerScreen::StartServer()
{
    startServerButton->setColor(sf::Color::Green);
    Lobby* chat = Lobby::Server(port);
}

void ServerScreen::StartClient()
{

}
        


