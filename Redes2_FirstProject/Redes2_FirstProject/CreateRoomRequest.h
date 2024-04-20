#pragma once
#include "Codable.h"
#include "RoomData.h"
class RoomRequestData : public ICodable{
public:
	RoomRequestData(Packet & p) {
		Code(p);	
	}
	void Code(sf::Packet & packet) override {
		packet /*<< packetKey*/ << data;
	}
	void Decode(sf::Packet & packet) override {
		packet >> data;
	}
	RoomData data;
};

