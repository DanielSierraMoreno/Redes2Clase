#pragma once
#include <string>
#include <mutex>
#include <SFML/Network.hpp>
#include <vector>
#include <list>
class Chat
{
private:
	bool _isServer = false;
	std::mutex _isServerMutex;
	std::list<sf::TcpSocket*> _sockets;
	std::mutex _socketMutex;

	sf::IpAddress _serverAddress;

	std::vector<std::string> _messages;
	std::mutex _messageMutex;

	Chat() {}
	void ShowMessage(std::string message);
	void ShowWarning(std::string message);
	void ShowError(std::string message);

	void ListenClientsConnections(unsigned short port);
	void ConnectToServer(std::string ip, unsigned short port);


	void OnClientEnter(sf::TcpSocket* client);
	void ListenMessages(sf::TcpSocket* socket);
	void ListenKeyboardToSendMessages();
	void SendMessage(std::string message);
	bool CheckError(sf::Socket::Status STATUS, std::string error);

public:
	static Chat* Server(unsigned short port);
	static Chat* Client(std::string ip, unsigned short port);
};

	