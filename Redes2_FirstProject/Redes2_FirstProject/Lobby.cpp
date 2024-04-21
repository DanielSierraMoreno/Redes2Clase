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
            lobbyMutex->lock();

            game->roomId = color->roomId;
            game->visible = true;
            game->currentPlayer->playerColor = playerColor;

            for (int i = 0; i < color->messages.size(); i++)
            {
                game->PrintMessage(color->messages[i]->messageName.name, color->messages[i]->message.name);
            }

            for (int i = 0; i < color->selectedPositions.size(); i++)
            {


                game->SelectPiece(Vector2D(color->selectedPositions[i]->x, color->selectedPositions[i]->y));
                game->ReleasePiece(Vector2D(color->releasedPositions[i]->x, color->releasedPositions[i]->y));

            }


            lobbyMutex->unlock();




            game->SetPlayer();

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

        socket->Subscribe(SelectPiece, [socket, this](Packet p) {

            Position* posInfo = new Position(p);
            playersMutex.lock();


            game->SelectPiece(Vector2D(posInfo->x, posInfo->y));

            playersMutex.unlock();

        });
        socket->Subscribe(ReleasePiece, [socket, this](Packet p) {

            Position* posInfo = new Position(p);
            playersMutex.lock();

            game->ReleasePiece(Vector2D(posInfo->x, posInfo->y));

            playersMutex.unlock();

            });
        socket->Subscribe(StartGame, [socket, this](Packet p) {

            playersMutex.lock();

                game->gameStarted = true;
                game->RemoveDrawable(&game->filtro);
            
                PlayersNames* names = new PlayersNames(p);

                game->playerWhite->text.setString(names->playerWhiteName);
                game->playerBlack->text.setString(names->playerBlackName);

                game->RemoveDrawable(game->startButton);

                delete game->startButton;

            playersMutex.unlock();


            });
        socket->Subscribe(SendMessageToClients, [socket, this](Packet p) {
            Message* messageInfo = new Message(p);
            playersMutex.lock();
            game->PrintMessage(messageInfo->messageName.name, messageInfo->message.name);
          
            playersMutex.unlock();

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

        socket->Subscribe(TryToStartGame, [socket, this, playerID](Packet packet) {

            EnterRoom* room = new EnterRoom(packet);

            RoomInfo* info = roomsInfo.roomsInfo[room->id];
            lobbyMutex->lock();

            info->startGame++;



            PlayersNames* names = new PlayersNames();
            names->playerWhiteName = info->playersNames[0]->name;

            names->playerBlackName = info->playersNames[1]->name;
            Packet players;
            names->Code(players);

            if (info->startGame >= 2)
            {
                for (auto it = info->playersInRoom.begin(); it != info->playersInRoom.end(); it++) {


                        if (!it->second.second->Send(StartGame, players))
                            std::cout << "Failed to enter as spectator" << std::endl;
                        else
                            std::cout << "Enter as spectator succes" << std::endl;
    

                }
            }
            lobbyMutex->unlock();

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
                CPInt* id = new CPInt(playerID);
                info->playersInRoom.insert(std::make_pair(id->id, playersInLobby[id->id]));

                if (info->playersNames.size() == 1)
                {
                    PlayerType* color = new PlayerType(-1);
                    color->roomId = data->id;
                    color->messages = info->messages;
                    color->selectedPositions = info->selectedPositions;
                    color->releasedPositions = info->releasedPositions;

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
                    color->roomId = data->id;
                    color->messages = info->messages;
                    color->selectedPositions = info->selectedPositions;
                    color->releasedPositions = info->releasedPositions;
                    Packet playerColorToSend;
                    color->Code(playerColorToSend);



                    if (!socket->Send(PlayerColor, playerColorToSend))
                        std::cout << "Failed to enter as player" << std::endl;
                    else
                        std::cout << "Enter as player" << std::endl;
                }
                    
            }

           playersMutex.unlock();




            });
        socket->Subscribe(EnterAsSpectator, [socket, this, playerID](Packet packet) {
            EnterRoom* data = new EnterRoom(packet);
            playersMutex.lock();

            RoomInfo* info = roomsInfo.roomsInfo[data->id];

 
            CPString* name = new CPString(data->name);
            info->spectatorsNames.push_back(name);
            CPInt* id = new CPInt(playerID);

            info->playersInRoom.insert(std::make_pair(id->id, playersInLobby[id->id]));

            PlayerType* color = new PlayerType(2);
            color->roomId = data->id;
            color->messages = info->messages;
            color->selectedPositions = info->selectedPositions;
            color->releasedPositions = info->releasedPositions;
            Packet playerColorToSend;
            color->Code(playerColorToSend);


            


            if (!socket->Send(PlayerColor, playerColorToSend))
                std::cout << "Failed to enter as spectator" << std::endl;
            else
                std::cout << "Enter as spectator succes" << std::endl;



            playersMutex.unlock();


            });
        socket->Subscribe(SendSelectedPiece, [socket, this, playerID](Packet packet) {

            Position* posInfo = new Position(packet);
            playersMutex.lock();

            RoomInfo* info = roomsInfo.roomsInfo[posInfo->roomId];

            bool select = posInfo->select;

            if (select)
            {
                info->currentSelectedPosition = posInfo;
            }
            else
            {
                info->selectedPositions.push_back(info->currentSelectedPosition);

                info->releasedPositions.push_back(posInfo);
            }

 
            for (auto it = info->playersInRoom.begin(); it != info->playersInRoom.end(); it++) {
                

                    Position* sendPos = posInfo;
                    Packet sendPosition;
                    sendPos->Code(sendPosition);

                    if (select)
                    {
                        Position* newPos = new Position();
                        newPos->x = posInfo->x;
                        newPos->y = posInfo->y;

                        if (!it->second.second->Send(SelectPiece, sendPosition))
                            std::cout << "Failed to enter as spectator" << std::endl;
                        else
                            std::cout << "Enter as spectator succes" << std::endl;
                    }
                    else {
                        Position* newPos = new Position();
                        newPos->x = posInfo->x;
                        newPos->y = posInfo->y;


                        if (!it->second.second->Send(ReleasePiece, sendPosition))
                            std::cout << "Failed to enter as spectator" << std::endl;
                        else
                            std::cout << "Enter as spectator succes" << std::endl;
                    }

            }

            playersMutex.unlock();

        });
        socket->Subscribe(SendMessageToServer, [socket, this, playerID](Packet packet) {

            Message* messageInfo = new Message(packet);
            playersMutex.lock();

            roomsInfo.roomsInfo[messageInfo->roomId]->messages.push_back(messageInfo);

            RoomInfo* info = roomsInfo.roomsInfo[messageInfo->roomId];

            for (auto it = info->playersInRoom.begin(); it != info->playersInRoom.end(); it++) {

                Packet messagePacket;

                messageInfo->Code(messagePacket);

                if (!it->second.second->Send(SendMessageToClients, messagePacket))
                    std::cout << "Failed tosend message to client" << std::endl;
                else
                    std::cout << "Message send t client" << std::endl;
    

            }
 
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
    chat->playerColor = NONE;

    chat->game = new Board(1450, 850, "Game", chat);
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