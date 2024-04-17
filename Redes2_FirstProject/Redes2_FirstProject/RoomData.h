#pragma once
#include <string>
#include <vector>
#include "Address.h"
class RoomData
{
public:
	RoomData();
	RoomData(std::string id, std::string name, __time32_t _timestamp);
	std::string id;
	std::string name;
	__time32_t timestamp;
};

