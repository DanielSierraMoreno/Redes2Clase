// Redes2_FirstProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include "ConsoleControl.h"
#include <SFML/Network.hpp>
#include "lobby.h"
#include <SFML/Graphics.hpp>
#include "Board.h"

#include "SocketsManager.h"
#include "Window.h"
#include "RoomManager.h"
#include "MainScreen.h"
#include "ScreenManager.h"
void RunClient();
void RunServer();
void RunWindows();



int main()
{
    sf::TcpSocket socket;
    char mode;

    RoomManager manager;

    MainScreen* mainScreen = new MainScreen(800, 800, "MainScreen");
    ScreenManager::getInstance().AddScreen(mainScreen);

    //board.run();

    while (true)
    {
        ScreenManager::getInstance().UpdateAllScreens();
    }
}

void RunClient() 
{
   /* std::cout << "Client";

    std::cout << std::endl << "Set server IP --> ";

    std::string ip;
    std::getline(std::cin, ip);

    Chat* chat = Chat::Client(ip, port);
    return;
    SocketsManager* SM = new SocketsManager([](TcpSocket* socket) //Al crear un SocketsManager hem de passar una funcio lambda al constructor
        {                                                         //que es guardara a una variable privada de la clase
                                                                  //per tal que quan es conecti un TcpSocket pasarlo com a parametre. 
                                                                  //(veure SocketsManager::AddSocket(TcpSocket* socket) per entendreho)
                                                                  //Per tant, tots els sockets que conectem implementaran la funcionalitat seguent:

            std::cout << std::endl << "Socket connected: " << socket->getRemoteAddress().toString();

            socket->Subscribe(Message, [socket](Packet packet) { //El TcpSocket que passem com a parametre te una variable map de keys y lambdas per tal que cada
                                                                 //instruccio que rebi el socket (key) corresponngui a una accio concreta (lambda).
                                                                 //En aquest cas, volem que la key "Message" tingui una lambda que printi el missatge que 
                                                                 //hi ha dins el paquet que hem rebut y envii una resposta a que ens ha enviat el missatge
                                                                  
                                                                 
                std::string message;
                packet >> message;
                std::cout << std::endl << "New Message: " << message;

                std::string response = "Pues Yo Soy El Cliente";
                Packet responsePacket;
                responsePacket << response;

                socket->Send(Message, responsePacket);
            });
            socket->SubscribeOnDisconnect([](TcpSocket* socket) {//El TcpSocket que passem com a parametre te una variable list de lambdas a executar quan es desconecti.
                                                                 //En aquest cas passem una lambda que fa un print del TcpSocket que sha desconectat

                std::cout << std::endl << "Socket disconected: " << socket->getRemoteAddress().toString();
            });
        });

    if (SM->ConnectToServer(ip,port)) //Intentarem conectar el socket al servidor
    {
        SM->StartLoop(); //Si el podem conectar começarem el bucle d'execucio
    }
    */
}


void RunServer()
{
}

