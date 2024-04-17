#include "MainScreen.h"
#include "Text.h"
#include "ServerScreen.h"
#include "ClientScreen.h"
#include "thread"
#include "ScreenManager.h"
MainScreen::MainScreen(int W, int H, std::string name) : Screen(W,H,name)
{
	startServerButton = new Button(GetMiddleScreenX() + 200, GetMiddleScreenY(), TextureManager::getInstance().buttonTexture);
	startServerButton->CenterPivot();
	startServerButton->setColor(sf::Color::Magenta);
	startServerButton->AddOnClickListener([this]() {
		OpenServerScreen();
		});
	AddDraweable(startServerButton);

	Text* text = new Text(startServerButton->GetMiddlePosX(), startServerButton->GetMiddlePosY(), "Server", 30);
	text->CenterText();
	AddDraweable(&text->text);

	startClientButton = new Button(GetMiddleScreenX() - 200, GetMiddleScreenY(), TextureManager::getInstance().buttonTexture);
	startClientButton->CenterPivot();
	startClientButton->setColor(sf::Color::Yellow);
	startClientButton->AddOnClickListener([this]() {
		OpenClientScreen();
		});
	AddDraweable(startClientButton);

	Text* text2 = new Text(startClientButton->GetMiddlePosX(), startClientButton->GetMiddlePosY(), "Client", 30);
	text2->CenterText();
	AddDraweable(&text2->text);

}

void MainScreen::OpenServerScreen()
{
	ServerScreen* serverScreen = new ServerScreen(400, 400, "Server Screen");
	ScreenManager::getInstance().AddScreen(serverScreen);


}

void MainScreen::OpenClientScreen()
{
	ClientScreen* clientScreen = new ClientScreen(400, 400, "Client Screen");
	ScreenManager::getInstance().AddScreen(clientScreen);
}
