#include "MainScreen.h"
#include "Text.h"
#include "ServerScreen.h"
#include "ClientScreen.h"
#include "thread"
#include "ScreenManager.h"
MainScreen::MainScreen(int W, int H, std::string name) : Screen(W,H,name,true)
{
	visible = true;

	startServerButton = new Button(GetMiddleScreenX() + 200, GetMiddleScreenY(), TextureManager::getInstance().buttonTexture,"Server",this,40);
	startServerButton->CenterPivot();
	startServerButton->setColor(sf::Color::Magenta);
	startServerButton->AddOnClickListener([this]() {
		OpenServerScreen();
		});



	startClientButton = new Button(GetMiddleScreenX() - 200, GetMiddleScreenY(), TextureManager::getInstance().buttonTexture, "Client",this,40);
	startClientButton->CenterPivot();
	startClientButton->setColor(sf::Color::Yellow);
	startClientButton->AddOnClickListener([this]() {
		OpenClientScreen();
		});



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
