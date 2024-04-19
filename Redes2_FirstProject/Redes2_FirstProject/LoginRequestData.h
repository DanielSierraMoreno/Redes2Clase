#pragma once
#include "Codable.h"
struct LoginRequestData : public ICodable { 

	LoginRequestData(std::string _name, Packet& packet) { name = _name; Code(packet); }
	LoginRequestData(Packet& packet) { Decode(packet); }
	std::string name;

	// Heredado vía ICodable
	void Code(sf::Packet& packet) override {
		packet /*<< packetKey*/ << name;
	}
	void Decode(sf::Packet& packet) override {
		packet >> name;
	}
};