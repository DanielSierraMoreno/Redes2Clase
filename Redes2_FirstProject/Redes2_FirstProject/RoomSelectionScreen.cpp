#include "RoomSelectionScreen.h"
#include "time.h";
#include <thread>
#include "Utils.h"

RoomSelectionScreen::RoomSelectionScreen(int W, int H, std::string name) : Screen(W,H,name)
{
	newRoomName = new InputText(200, 50, "Room name: ", this);
	newRoomName->AddDraweable();
	newRoomName->StartTyping();
	Button* createRoomButton  = new Button(450, 50,TextureManager::getInstance().buttonTexture, "Create Room",this,20);
	createRoomButton->CenterPivot();
	createRoomButton->setColor(sf::Color::Magenta);
	createRoomButton->AddOnClickListener([this]() {
		CreateRoom();
		});
	createRoomButton->setScale(0.75f,0.25f);


}

void RoomSelectionScreen::CreateRoom()
{
	time_t current_time = time(NULL);
	__time32_t timestamp = (__time32_t)current_time;

	if (newRoomName->stringContent == "")
		return;

	int x = 200;
	if (rooms.size() != 0)
	{
		x = rooms[rooms.size()-1]->background->getPosition().x + 300;
	}

	RoomData* roomData = new RoomData((int)rooms.size(), newRoomName->stringContent, Utils::timestamp32ToString(timestamp));

	RoomPrefab* prefab = new RoomPrefab(x, 300, roomData, this);
	rooms.push_back(prefab);


	newRoomName->stringContent = "";
	newRoomName->UpdateTextContent(false);
}

void RoomSelectionScreen::SetData(Lobby* data)
{
	clientData = data;
}

void RoomSelectionScreen::Update()
{
	Draw();
	Events();

	for (int i = 0; i < rooms.size(); i++)
	{
		rooms[i]->UpdatePosition(GetScroll());

	}
		ResetScroll();

}
