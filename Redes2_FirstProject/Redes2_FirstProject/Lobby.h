#pragma once
#include <string>
#include <mutex>
#include <SFML/Network.hpp>
#include <vector>
#include <list>
#include "RoomData.h"
#include "SocketsManager.h"
#include "RoomsUpdate.h"
#include "Pieces.h"
#include "Board.h"
#include "Codable.h"

enum PackagesIds : Packet::PacketKey { RoomsUpdate = 0, OnLogin = 1, CreateRoomRequest = 2, CreateRoomResponse = 3, EnterAsPlayer = 4, EnterAsSpectator = 5, PlayerColor = 6, SelectPiece = 7, ReleasePiece = 8, TryToStartGame = 9, SendSelectedPiece = 10, SendReleasedPiece = 11  };

class Lobby
{
private:
	unsigned short port;
	bool _isServer = false;

	PieceColor playerColor;

	RoomsInfo roomsInfo;
	Board* game;

	sf::IpAddress _serverAddress;

	std::vector<std::string> _messages;
	std::mutex _messageMutex;

	SocketsManager* SM;
	std::mutex* lobbyMutex,playersMutex;
	RoomsUpdateData roomsData;
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
	std::string GetPlayerName() { return PlayerName; };
	static Lobby* Server(unsigned short _port);
	static Lobby* Client(std::string name,std::string ip, unsigned short port);
	bool CheckIfEnterServer();
	TcpSocket* serverSocket;
	CPVector<RoomData> GetRoomsData();

	void EnterRoomAsPlayer(std::string name, int id);
	void EnterRoomAsSpectator(std::string name, int id);

};




class PlayerType : public ICodable {
public:
	PlayerType(Packet& p) {
		Decode(p);
	}
	PlayerType(int color) { playerColor = color; }
	int playerColor;
	int roomId = 0;

	void Code(sf::Packet& packet) override {
		packet /*<< packetKey*/ << playerColor << roomId;
	}
	void Decode(sf::Packet& packet) override {
		packet >> playerColor >> roomId;
	}
};
