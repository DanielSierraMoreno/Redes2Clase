#include "lobby.h"
#include <iostream>
#include <thread>
#include "ConsoleControl.h"
#include "LoginRequestData.h"

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

void Lobby::ConnectToServer(std::string name, std::string ip, unsigned short port)
{
    PlayerName = name;

    SM = new SocketsManager([this](int id, TcpSocket* socket) {

        socket->Subscribe(RoomsUpdate, [socket, this](Packet p) {

            std::cout << "Client Received a RoomUpdate" << std::endl;

            lobbyMutex->lock();
            if (roomsData == nullptr)
                roomsData = new RoomsUpdateData(p);
            else {
                roomsData->rooms.clear();
                roomsData->Decode(p);
            }
            lobbyMutex->unlock();
            });
            Packet loginPacket;
            LoginRequestData loginData(PlayerName, loginPacket);
            if (socket->Send(OnLogin, loginPacket))
                std::cout << "Logged" << std::endl;
            else
                std::cout << "Failed to log in" << std::endl;

        });

    if (SM->ConnectToServer(ip, port)) {
        SM->StartLoop();
    }
}

void Lobby::CreateServer()
{
    SM = new SocketsManager([this](int playerID, TcpSocket* socket) {

        std::cout << std::endl << "Socket connected: " << socket->getRemoteAddress().toString();

        socket->Subscribe(OnLogin, [socket, this, playerID](Packet packet) {

            LoginRequestData data(packet);

            Packet roomsDataPacket;

            lobbyMutex->lock();
            if (roomsData != nullptr)
                roomsData->Code(roomsDataPacket);
            else
                roomsData = new RoomsUpdateData(roomsDataPacket);
            lobbyMutex->unlock();

            lobbyMutex->lock();
            playersInLobby.insert(std::make_pair(playerID, std::make_pair(data.name, socket)));
            lobbyMutex->unlock();

            if (!socket->Send(RoomsUpdate, roomsDataPacket))
                std::cout << "Server failed to send room update" << std::endl;
            else
                std::cout << "Loaded a total of" << roomsData->rooms.size() << std::endl;

            });

        });

    if (SM->StartListener(port))
    {
        std::cout << "Listening on Ip: " << _serverAddress.toString() << std::endl;
        SM->StartLoop();
    }
    else
        std::cout << "Error on turning server up" << std::endl;
}

Lobby* Lobby::Server(unsigned short _port)
{
    Lobby* chat = new Lobby();
    chat->_serverAddress = sf::IpAddress::getLocalAddress();
    chat->_isServer = true;
    chat->port = _port;
    chat->CreateServer();

    return chat;
}

Lobby* Lobby::Client(std::string name, std::string ip, unsigned short port)
{
    Lobby* chat = new Lobby();
    chat->_serverAddress = sf::IpAddress(ip);

    chat->ConnectToServer(name, ip, port);

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