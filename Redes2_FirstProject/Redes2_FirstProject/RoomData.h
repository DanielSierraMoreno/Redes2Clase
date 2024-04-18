#pragma once
#include <string>
#include <vector>
#include "Address.h"
class RoomData
{
public:
	RoomData();
	RoomData(unsigned long id, std::string name, __time32_t _timestamp);
	unsigned long id;
	std::string name;
	__time32_t timestamp;
};

