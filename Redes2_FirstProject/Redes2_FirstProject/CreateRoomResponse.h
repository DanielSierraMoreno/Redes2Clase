#pragma once
#include "Codable.h"
class CreateRoomResponse : public ICodable { 
	sf::Uint64 id; 

	void Code(sf::Packet& packet) override {
		packet /*<< packetKey*/ << id;
	}
	void Decode(sf::Packet& packet) override {
		packet >> id;
	}
};

