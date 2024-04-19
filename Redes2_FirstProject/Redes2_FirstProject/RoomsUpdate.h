#pragma once
#include <vector>
#include "RoomData.h"
#include "Codable.h"

class RoomsUpdateData : public ICodable {
public:
	RoomsUpdateData(Packet& p) {
		Code(p);
	}
	void Code(sf::Packet& packet) override {
		packet /*<< packetKey*/ << rooms;
	}
	void Decode(sf::Packet& packet) override {
		packet >> rooms;
	}
	CPVector<RoomData> rooms;

};
