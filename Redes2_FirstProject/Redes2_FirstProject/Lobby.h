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

enum PackagesIds : Packet::PacketKey { RoomsUpdate = 0, OnLogin = 1, CreateRoomRequest = 2, CreateRoomResponse = 3, EnterAsPlayer = 4, EnterAsSpectator = 5, PlayerColor = 6, 
	SelectPiece = 7, ReleasePiece = 8, TryToStartGame = 9, SendSelectedPiece = 10, SendReleasedPiece = 11, StartGame = 12, SendMessageToServer = 13, SendMessageToClients =14 };

class Lobby
{
private:
	unsigned short port;
	bool _isServer = false;


	PieceColor playerColor;

	RoomsInfo roomsInfo;
	Board* game;

	sf::IpAddress _serverAddress;

	std::vector<Message> _messages;
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
	bool sendMessage;
	PieceColor GetPlayerType() { return playerColor;  }
	bool IsSpectator() { return playerColor == NONE; }
	std::string GetPlayerName() { return PlayerName; };
	static Lobby* Server(unsigned short _port);
	static Lobby* Client(std::string name,std::string ip, unsigned short port);
	bool CheckIfEnterServer();
	TcpSocket* serverSocket;
	CPVector<RoomData> GetRoomsData();

	void EnterRoomAsPlayer(std::string name, int id);
	void EnterRoomAsSpectator(std::string name, int id);

};


class PlayersNames : public ICodable {
public:
	PlayersNames(Packet& p) {
		Decode(p);
	}
	PlayersNames() = default;

	std::string playerWhiteName;
	std::string playerBlackName;

	void Code(sf::Packet& packet) override {
		packet /*<< packetKey*/ << playerWhiteName << playerBlackName;
	}
	void Decode(sf::Packet& packet) override {
		packet >> playerWhiteName >> playerBlackName;
	}
};



class PlayerType : public ICodable {
public:
	PlayerType(Packet& p) {
		Decode(p);
	}
	PlayerType(int color) { playerColor = color; }
	int playerColor;
	int roomId = 0;
	CPVector<Message> messages;

	CPVector<Position> selectedPositions;
	CPVector<Position> releasedPositions;


	void Code(sf::Packet& packet) override {
		packet /*<< packetKey*/ << playerColor << roomId<< messages << selectedPositions << releasedPositions;
	}
	void Decode(sf::Packet& packet) override {
		packet >> playerColor >> roomId >> messages >> selectedPositions >> releasedPositions;
	}
};
