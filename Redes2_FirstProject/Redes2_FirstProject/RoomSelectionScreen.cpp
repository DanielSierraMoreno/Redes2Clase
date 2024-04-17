#include "RoomSelectionScreen.h"
#include "time.h";
RoomSelectionScreen::RoomSelectionScreen(int W, int H, std::string name) : Screen(W,H,name)
{
	newRoomName = new InputText(200, 50, "Room name: ", this);
	newRoomName->AddDraweable();
	newRoomName->StartTyping();
	Button* createRoomButton  = new Button(GetMiddleScreenX() + 200, GetMiddleScreenY(),TextureManager::getInstance().buttonTexture);
	createRoomButton->CenterPivot();
	createRoomButton->setColor(sf::Color::Magenta);
	createRoomButton->AddOnClickListener([this]() {
		CreateRoom();
		});
	AddDraweable(createRoomButton);

	Text* text = new Text(createRoomButton->GetMiddlePosX(), createRoomButton->GetMiddlePosY(), "Create Room", 30);
	text->CenterText();
	AddDraweable(&text->text);
}

void RoomSelectionScreen::CreateRoom()
{
	time_t current_time = time(NULL);
	__time32_t timestamp = (__time32_t)current_time;
	RoomPrefab* prefab = new RoomPrefab(0,0,new RoomData("" + (int)rooms.size(), newRoomName->stringContent, timestamp), this);
	rooms.push_back(prefab);
}

void RoomSelectionScreen::SetData(Lobby* data)
{
	clientData = data;
}
