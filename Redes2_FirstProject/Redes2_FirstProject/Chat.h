#pragma once
#include <string>
#include <mutex>
#include <SFML/Network.hpp>
#include <vector>
#include <list>
#include "RoomData.h"

class Lobby
{
private:
	bool _isServer = false;
	std::mutex _isServerMutex;
	std::list<sf::TcpSocket*> _sockets;
	std::mutex _socketMutex;

	sf::IpAddress _serverAddress;

	std::vector<std::string> _messages;
	std::mutex _messageMutex;

	std::vector<RoomData> rooms;


	bool enterServer = false;
	Lobby() {}
	void ShowMessage(std::string message);
	void ShowWarning(std::string message);
	void ShowError(std::string message);

	void ListenClientsConnections(unsigned short port);
	void ConnectToServer(std::string ip, unsigned short port);


	void OnClientEnter(sf::TcpSocket* client);
	void OnClientCreateRoom(sf::TcpSocket* client);
	void ListenMessages(sf::TcpSocket* socket);
	void ListenKeyboardToSendMessages();
	void SendMessage(std::string message);
	bool CheckError(sf::Socket::Status STATUS, std::string error);

public:
	static Lobby* Server(unsigned short port);
	static Lobby* Client(std::string ip, unsigned short port);
	bool CheckIfEnterServer();
};

	