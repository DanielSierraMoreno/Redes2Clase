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

	name = new Text(x,y + bounds.height, data->name, 20);
	name->CenterText();
	currentScreen->AddDraweable(&name->text);

	createdTime = new Text(x, y + bounds.height + 20,Utils::timestamp32ToString(_data->timestamp), 20);
	createdTime->CenterText();
	currentScreen->AddDraweable(&createdTime->text);



	enterAsPlayer = new Button(x,y - 100, TextureManager::getInstance().buttonTexture);
	enterAsPlayer->PivotCorner();
	enterAsPlayer->setScale(0.35, 0.2);
	enterAsPlayer->setColor(sf::Color::Red);
	enterAsPlayer->AddOnClickListener([this]() {
		});
	currentScreen->AddDraweable(enterAsPlayer);

	Text* text1 = new Text(enterAsPlayer->GetMiddlePosX() - 38, enterAsPlayer->GetMiddlePosY() - 25, "Connect", 20);
	text1->CenterText();
	currentScreen->AddDraweable(&text1->text);

	enterAsSpectator = new Button(x, y -150, TextureManager::getInstance().buttonTexture);
	enterAsSpectator->PivotCorner();
	enterAsSpectator->setScale(0.35, 0.2);
	enterAsSpectator->setColor(sf::Color::Red);
	enterAsSpectator->AddOnClickListener([this]() {
		});
	currentScreen->AddDraweable(enterAsSpectator);

	Text* text2 = new Text(enterAsSpectator->GetMiddlePosX() - 38, enterAsSpectator->GetMiddlePosY() - 25, "Connect", 20);
	text2->CenterText();
	currentScreen->AddDraweable(&text2->text);
}
