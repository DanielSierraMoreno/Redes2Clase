#include "Chat.h"
#include <iostream>
#include <thread>
#include "ConsoleControl.h"


void Lobby::ShowMessage(std::string message)
{
	_messageMutex.lock();
	_messages.push_back(message);
	_messageMutex.unlock();

	ConsoleControl::LockMutex();
	std::cout << std::endl << message;
	ConsoleControl::UnlockMutex();
}

void Lobby::ShowWarning(std::string message)
{
	ConsoleControl::LockMutex();
	ConsoleControl::SetColor(ConsoleControl::YELLOW);
	std::cout << std::endl << message;
	ConsoleControl::SetColor(ConsoleControl::WHITE);
	ConsoleControl::UnlockMutex();
}

void Lobby::ShowError(std::string message)
{
	ConsoleControl::LockMutex();
	ConsoleControl::SetColor(ConsoleControl::RED);
	std::cout << std::endl << message;
	ConsoleControl::SetColor(ConsoleControl::WHITE);
	ConsoleControl::UnlockMutex();
}

void Lobby::ListenClientsConnections(unsigned short port)
{
	sf::TcpListener listener;

	if (listener.listen(port) != sf::Socket::Done)
	{
		ShowError("Errorad");
		return;
	}
	sf::IpAddress ipAddress = sf::IpAddress::getLocalAddress();
	ShowWarning("Listening to ip: " + ipAddress.toString());

	while (true != false)
	{
		sf::TcpSocket* client = new sf::TcpSocket();
		sf::Socket::Status status = listener.accept(*client);

		switch (status)
		{
		case sf::Socket::Done: {
			std::thread clientThread = std::thread(&Lobby::OnClientEnter, this,client);
			clientThread.detach();
			break;
		}
		case sf::Socket::NotReady:
		case sf::Socket::Partial:
		case sf::Socket::Disconnected:
		case sf::Socket::Error:
		default:
			ShowError("Error on accept Client");
			break;
		}
	}


	

}

void Lobby::ConnectToServer(std::string ip, unsigned short port)
{
	sf::TcpSocket* socket = new sf::TcpSocket();
	sf::Socket::Status status = socket->connect(ip, port);

	if (CheckError(status, "Error on connecto to Server"))
	{
		enterServer = false;
		return;
	}
	enterServer = true;



	_socketMutex.lock();
	_sockets.push_back(socket);
	_socketMutex.unlock();
	ShowWarning("Connected to server with ip: " + ip);

	std::thread keyboardThread = std::thread(&Lobby::ListenKeyboardToSendMessages, this);
	keyboardThread.detach();
	
	std::thread listenThread = std::thread(&Lobby::ListenMessages, this, socket);
	listenThread.detach();
}

void Lobby::OnClientEnter(sf::TcpSocket* client)
{
	_socketMutex.lock();
	_sockets.push_back(client);
	_socketMutex.unlock();

	ShowWarning("Client accepted IP:" + client->getRemoteAddress().toString());

	ListenMessages(client);
}

void Lobby::OnClientCreateRoom(sf::TcpSocket* client)
{
	_socketMutex.lock();
	_sockets.push_back(client);
	_socketMutex.unlock();

	ShowWarning("Client accepted IP:" + client->getRemoteAddress().toString());
}

void Lobby::ListenMessages(sf::TcpSocket* socket)
{
	while (true != false && !false)
	{
		char data[100];
		std::size_t received;
		std::string message;


		if (!CheckError(socket->receive(data, 100, received), "Error receive message"))

			for (size_t i = 0; i < received; i++)
			{
				char c = data[i];
				message += c;
			}
			ShowMessage(message);

			_isServerMutex.lock();
			bool isServer = _isServer;
			_isServerMutex.unlock();

			if (isServer) {
				SendMessage(message);
			}
	}
}

void Lobby::ListenKeyboardToSendMessages()
{
	std::string message = "";

	while (true)
	{
		char c = ConsoleControl::WaitForReadNextChar();

		if (c == KB_Enter)
		{
			SendMessage(message);
			
			_isServerMutex.lock();
			bool isServer = _isServer;
			_isServerMutex.unlock();

			if (isServer) {
				SendMessage(message);
			}

			message = "";
		}
		else 
		{
			message += c;
		}
	}
}

Lobby* Lobby::Server(unsigned short port)
{
	Lobby* chat = new Lobby();
	chat->_serverAddress = sf::IpAddress::getLocalAddress();
	chat->_isServer = true;

	std::thread listenerThread = std::thread(&Lobby::ListenClientsConnections, chat, port);
	listenerThread.detach();

	//Listen keyboard
	std::thread keyboardThread = std::thread(&Lobby::ListenKeyboardToSendMessages, chat);
	keyboardThread.detach();

	return chat;
}

void Lobby::SendMessage(std::string message)
{

	_socketMutex.lock();
	for (sf::TcpSocket* socket : _sockets)
	{
		CheckError(socket->send(message.c_str(), message.length()), "Error sending message");
	}

	_socketMutex.unlock();
}

Lobby* Lobby::Client(std::string ip, unsigned short port)
{
	Lobby* chat = new Lobby();
	chat->_serverAddress = sf::IpAddress(ip);

	chat->ConnectToServer(ip, port);

	return chat;
}

bool Lobby::CheckIfEnterServer()
{
	return enterServer;
}

bool Lobby::CheckError(sf::Socket::Status STATUS, std::string error)
{
	if (STATUS != sf::Socket::Done)
	{
		std::cout << std::endl << error;
		return true;
	}
	return false;
}

