#include "RoomPrefab.h"
#include "Utils.h"



RoomPrefab::RoomPrefab()
{
}

RoomPrefab::RoomPrefab(int x, int y, RoomData* _data, Screen* currentScreen)
{
	data = _data;

	background = new sf::Sprite(TextureManager::getInstance().buttonTexture);
	background->setColor(sf::Color(100, 100, 100, 255));
	sf::FloatRect bounds = background->getLocalBounds(); 
	background->setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	background->setPosition(x, y);
	background->setScale(1.25f, 1.5f);
	currentScreen->AddDraweable(background);

	name = new Text(x,y-150, data->name, 20);
	name->CenterText();
	currentScreen->AddDraweable(&name->text);

	createdTime = new Text(x, y + bounds.height - 80,_data->timestamp, 20);
	createdTime->CenterText();
	currentScreen->AddDraweable(&createdTime->text);



	enterAsPlayer = new Button(x,y-65, TextureManager::getInstance().buttonTexture, "Enter As Player",currentScreen,30);
	enterAsPlayer->CenterPivot();
	enterAsPlayer->setScale(1.1, 0.5);
	enterAsPlayer->setColor(sf::Color::Red);
	enterAsPlayer->AddOnClickListener([this]() {
		});



	enterAsSpectator = new Button(x, y +65, TextureManager::getInstance().buttonTexture, "Enter As Spectator",currentScreen,30);
	enterAsSpectator->CenterPivot();
	enterAsSpectator->setScale(1.1, 0.5);
	enterAsSpectator->setColor(sf::Color::Red);
	enterAsSpectator->AddOnClickListener([this]() {
		});


}

void RoomPrefab::UpdatePosition(int x)
{

	background->setPosition(background->getPosition().x+x, background->getPosition().y);

	name->setPosition(name->posX + x, name->posY);

	createdTime->setPosition(createdTime->posX + x, createdTime->posY);



	enterAsPlayer->UpdatePosition(x);



	enterAsSpectator->UpdatePosition(x);

}
