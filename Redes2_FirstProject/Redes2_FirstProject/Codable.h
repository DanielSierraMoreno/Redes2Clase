#pragma once
#include "Packet.h"
#include <vector>
#include <list>


class ICodable
{
public:
	virtual void Code(sf::Packet& packet) = 0;
	virtual void Decode(sf::Packet& packet) = 0;
};

inline sf::Packet& operator <<(sf::Packet& packet, ICodable& codable)
{
	codable.Code(packet);
	return packet;
}

inline sf::Packet& operator >>(sf::Packet& packet, ICodable& codable)
{
	codable.Decode(packet);
	return packet;
}

class CPString : public ICodable
{
public:
	CPString() = default;
	CPString(std::string name) { this->name = name; }

	CPString(Packet& p) {
		Decode(p);
	}
	std::string name;

	void Code(sf::Packet& packet) override {
		packet << name;

	}
	void Decode(sf::Packet& packet) override {
		packet >> name;

	}


};


class CPInt : public ICodable
{
public:
	CPInt() = default;
	CPInt(int id) { this->id = id; }

	CPInt(Packet& p) {
		Decode(p);
	}
	int id;

	void Code(sf::Packet& packet) override {
		packet << id;

	}
	void Decode(sf::Packet& packet) override {
		packet >> id;

	}


};


class Position : public ICodable
{
public:
	Position() = default;
	Position(float X, float Y, int roomId, bool Select) { x = X; y = Y; this->roomId = roomId; select = Select; }

	Position(Packet& p) {
		Decode(p);
	}
	float x;
	float y;
	int roomId;
	bool select;


	void Code(sf::Packet& packet) override {
		packet << x << y << roomId << select;

	}
	void Decode(sf::Packet& packet) override {
		packet >> x >> y >> roomId >> select;

	}


};

template<typename T, typename = typename std::enable_if<std::is_base_of<ICodable, T>::value>::type>
class CPVector : public std::vector<T*>, public ICodable
{
	virtual void Code(sf::Packet& packet) override
	{
		sf::Uint64 count = this->size();
		packet << count;

		for (T* item : *this)
		{
			ICodable* codable = dynamic_cast<ICodable*>(item);
			codable->Code(packet);
		}
	}

	virtual void Decode(sf::Packet& packet) override
	{

		sf::Uint64 count;
		packet >> count;

		for (sf::Uint64 i = 0; i < count; i++)
		{
			T* item = new T();
			reinterpret_cast<ICodable*>(item)->Decode(packet);
			this->push_back(item);
		}
	}
};

template<typename T, typename = typename std::enable_if<std::is_base_of<ICodable, T>::value>::type>
class CPList : public std::list<T*>, public ICodable
{
public:
	virtual void Code(sf::Packet& packet) override
	{
		sf::Uint64 count = this->size();
		packet << count;

		for (T* item : *this)
		{
			ICodable* codable = dynamic_cast<ICodable*>(item);
			codable->Code(packet);
		}
	}

	virtual void Decode(sf::Packet& packet) override
	{
		sf::Uint64 count;
		packet >> count;

		for (sf::Uint64 i = 0; i < count; i++)
		{
			T* item = new T();
			reinterpret_cast<ICodable*>(item)->Decode(packet);
			this->push_back(item);
		}
	}
};