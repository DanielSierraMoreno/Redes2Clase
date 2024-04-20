#include "lobby.h"
#include <iostream>
#include <thread>
#include "ConsoleControl.h"
#include "LoginRequestData.h"
#include "CreateRoomRequest.h"
#include "Board.h"
#include "ScreenManager.h"

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
    lobbyMutex = new std::mutex();
    PlayerName = name;

    SM = new SocketsManager([this](int id, TcpSocket* socket) {
        serverSocket = socket;

        socket->Subscribe(PlayerColor, [socket, this](Packet packet) {
           
            PlayerType* color = new PlayerType(packet);

            playerColor = (PieceColor)color->playerColor;


            });

        socket->Subscribe(RoomsUpdate, [socket, this](Packet p) {

            std::cout << "Client Received a RoomUpdate" << std::endl;

            lobbyMutex->lock();
            if (roomsData.rooms.size() == 0)
            {
                RoomsUpdateData newRooms;
                newRooms.Decode(p);
                roomsData = newRooms;
            }

            else {
                roomsData.rooms.clear();
                roomsData.Decode(p);
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
    lobbyMutex = new std::mutex();
    SM = new SocketsManager([this](int playerID, TcpSocket* socket) {

        std::cout << std::endl << "Socket connected: " << socket->getRemoteAddress().toString();

        socket->Subscribe(OnLogin, [socket, this, playerID](Packet packet) {

            LoginRequestData data(packet);

            Packet roomsDataPacket;

            lobbyMutex->lock();
            if (roomsData.rooms.size() > 0)
                roomsData.Code(roomsDataPacket);
            else
                roomsData = RoomsUpdateData(roomsDataPacket);
            lobbyMutex->unlock();

            lobbyMutex->lock();
            playersInLobby.insert(std::make_pair(playerID, std::make_pair(data.name, socket)));
            lobbyMutex->unlock();

            if (!socket->Send(RoomsUpdate, roomsDataPacket))
                std::cout << "Server failed to send room update" << std::endl;
            else
                std::cout << "Loaded a total of" << roomsData.rooms.size() << std::endl;

            });
        socket->Subscribe(CreateRoomRequest, [socket, this, playerID](Packet packet) {

            RoomData* data = new RoomData(packet);
            Packet roomsPacketToSend;


            
            lobbyMutex->lock();
            RoomInfo* a = new RoomInfo();

            roomsInfo.roomsInfo.push_back(a);

            roomsData.rooms.push_back(data);
            roomsData.Code(roomsPacketToSend);
            lobbyMutex->unlock();

            playersMutex.lock();
            for (auto it = playersInLobby.begin(); it != playersInLobby.end(); it++) { 
            {
                    if (it->second.second->Send(RoomsUpdate, roomsPacketToSend)) {
                        std::cout << "Sending Update To All: " << std::endl;
                    }
                    else {
                        std::cout << "Sending Update Error: " << std::endl;
                    }
                }
            }
            playersMutex.unlock();
            });

        socket->Subscribe(EnterAsPlayer, [socket, this, playerID](Packet packet) {
            EnterRoom* data = new EnterRoom(packet);
            playersMutex.lock();

            RoomInfo* info = roomsInfo.roomsInfo[data->id];

            if (info->playersNames.size() < 2)
            {
                CPString* name = new CPString(data->name);
                info->playersNames.push_back(name);

                if (info->playersNames.size() == 1)
                {
                    PlayerType* color = new PlayerType(0);
                    Packet playerColorToSend;
                    color->Code(playerColorToSend);




                    if (!socket->Send(PlayerColor, playerColorToSend))
                        std::cout << "Failed to enter as player" << std::endl;
                    else
                        std::cout << "Enter as player" << std::endl;

                }
                else
                {
                    PlayerType* color = new PlayerType(1);
                    Packet playerColorToSend;
                    color->Code(playerColorToSend);



                    if (!socket->Send(PlayerColor, playerColorToSend))
                        std::cout << "Failed to enter as player" << std::endl;
                    else
                        std::cout << "Enter as player" << std::endl;
                }
                    
            }
           game = new Board(800, 600, "Game");
           ScreenManager::getInstance().AddScreen(game);
           playersMutex.unlock();




            });
        socket->Subscribe(EnterAsSpectator, [socket, this, playerID](Packet packet) {
            EnterRoom* data = new EnterRoom(packet);
            playersMutex.lock();

            RoomInfo* info = roomsInfo.roomsInfo[data->id];

 
            CPString* name = new CPString(data->name);
            info->spectatorsNames.push_back(name);
    
            PlayerType* color = new PlayerType(2);
            Packet playerColorToSend;
            color->Code(playerColorToSend);



            if (!socket->Send(PlayerColor, playerColorToSend))
                std::cout << "Failed to enter as spectator" << std::endl;
            else
                std::cout << "Enter as spectator succes" << std::endl;


            //game = new Board(1450, 850, "Lobby");
            //ScreenManager::getInstance().AddScreen(game);
            playersMutex.unlock();


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
    static Lobby* chat = new Lobby();
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


CPVector<RoomData> Lobby::GetRoomsData()
{
    return roomsData.rooms;
}

void Lobby::EnterRoomAsPlayer(std::string name, int id)
{
    
    EnterRoom* data = new EnterRoom(name,id);
    Packet roomsPacketToSend;

    lobbyMutex->lock();

    data->Code(roomsPacketToSend);
    lobbyMutex->unlock();


    if (!serverSocket->Send(EnterAsPlayer, roomsPacketToSend))
        std::cout << "Failed to enter as player" << std::endl;
    else
        std::cout << "Enter as player petition send" << std::endl;


}

void Lobby::EnterRoomAsSpectator(std::string name, int id)
{
    EnterRoom* data = new EnterRoom(name, id);
    Packet roomsPacketToSend;

    lobbyMutex->lock();

    data->Code(roomsPacketToSend);
    lobbyMutex->unlock();


    if (!serverSocket->Send(EnterAsSpectator, roomsPacketToSend))
        std::cout << "Failed to enter as spectator" << std::endl;
    else
        std::cout << "Enter as spectator" << std::endl;
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