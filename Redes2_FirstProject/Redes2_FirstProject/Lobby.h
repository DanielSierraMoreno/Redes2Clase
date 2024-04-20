#pragma once
#include <string>
#include <mutex>
#include <SFML/Network.hpp>
#include <vector>
#include <list>
#include "RoomData.h"
#include "SocketsManager.h"
#include "RoomsUpdate.h"

enum PackagesIds : Packet::PacketKey { RoomsUpdate = 0, OnLogin = 1, CreateRoomRequest = 2, CreateRoomResponse = 3};

class Lobby
{
private:
	unsigned short port;
	bool _isServer = false;

	sf::IpAddress _serverAddress;

	std::vector<std::string> _messages;
	std::mutex _messageMutex;

	SocketsManager* SM;
	std::mutex* lobbyMutex,playersMutex;
	RoomsUpdateData* roomsData;
	std::string PlayerName;

	std::map<int, std::pair<std::string, TcpSocket*>> playersInLobby;

	bool enterServer = false;
	Lobby() {}
	void ShowMessage(std::string message);
	void ShowWarning(std::string message);
	void ShowError(std::string message);

	void ConnectToServer(std::string name,std::string ip, unsigned short port);
	void CreateServer();

	bool CheckError(sf::Socket::Status STATUS, std::string error);

public:
	static Lobby* Server(unsigned short _port);
	static Lobby* Client(std::string name,std::string ip, unsigned short port);
	bool CheckIfEnterServer();
	TcpSocket* serverSocket;
	CPVector<RoomData> GetRoomsData();


};

	