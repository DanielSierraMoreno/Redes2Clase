#pragma once
#include "Screen.h"
#include "Chat.h"
#include "RoomPrefab.h"

class RoomSelectionScreen : public Screen
{
public:
	RoomSelectionScreen(int W, int H, std::string name);
	void CreateRoom();
	void SetData(Lobby* data);
	Lobby* clientData;
	std::vector<RoomPrefab*> rooms;

private:
	InputText* newRoomName;
};

