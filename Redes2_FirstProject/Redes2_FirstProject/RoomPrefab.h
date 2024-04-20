#pragma once
#include "Text.h";
#include "Button.h";
#include "RoomData.h"
#include "Screen.h"
class RoomPrefab
{
public:
	RoomPrefab();
	RoomPrefab(int x,int y,RoomData* _data,Screen* currentScreen);
	Text* name;
	Text* createdTime;
	sf::Sprite* background;
	Button* enterAsPlayer;
	Button* enterAsSpectator;
	RoomData* data;
	Screen* screen;
	void UpdatePosition(int x);
	~RoomPrefab();

};

