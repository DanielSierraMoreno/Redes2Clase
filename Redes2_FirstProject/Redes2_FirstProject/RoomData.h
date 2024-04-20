#pragma once
#include <string>
#include <vector>
#include "Address.h"
#include "Codable.h"
class RoomData : public ICodable
{
public:
	RoomData() = default;
	RoomData(Packet & p) {
		Decode(p);
	}
	RoomData(sf::Uint64 id, std::string name, std::string _timestamp);
	sf::Uint64 id;
	std::string name;
	std::string timestamp;

	void Code(sf::Packet& packet) override {
		packet << id << timestamp << name;
	}
	void Decode(sf::Packet& packet) override {
		packet >> id >> timestamp >> name;
	}
};


