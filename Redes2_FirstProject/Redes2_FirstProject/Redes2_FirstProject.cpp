// Redes2_FirstProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include "ConsoleControl.h"
#include <SFML/Network.hpp>
#include "Chat.h"
#include <SFML/Graphics.hpp>

#include "SocketsManager.h"
#include "Window.h"


void RunClient();
void RunServer();
void RunWindows();

unsigned short port = 3001;

enum PackagesIds: Packet::PacketKey { Message = 0};

int main()
{

    sf::TcpSocket socket;
    char mode;


    //RunWindows();

    do
    {
        std::cout << "Enter mode (S for Server, C for Client): ";
        mode = ConsoleControl::WaitForReadNextChar();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer del teclado

    } while (mode != 's' && mode != 'S' && mode != 'C' && mode != 'c');

    switch (mode)
    {
    case 'S':
    case 's':
        RunServer();
        break;
    case 'C':
    case 'c':
        RunClient();
        break;
    default:
        break;
    }


    while (true != false)
    {

    }
}
void RunClient() 
{
    std::cout << "Client";

    std::cout << std::endl << "Set server IP --> ";

    std::string ip;
    std::getline(std::cin, ip);

    //Chat* chat = Chat::Client(ip, port);

    SocketsManager* SM = new SocketsManager([](TcpSocket* socket)
        {
            std::cout << std::endl << "Socket connected: " << socket->getRemoteAddress().toString();

            socket->Subscribe(Message, [socket](Packet packet) {
                std::string message;
                packet >> message;
                std::cout << std::endl << "New Message: " << message;

                std::string response = "Pues Yo Soy El Cliente";
                Packet responsePacket;
                responsePacket << response;

                socket->Send(Message, responsePacket);
                });
            socket->SubscribeOnDisconnect([](TcpSocket* socket) {
                std::cout << std::endl << "Socket disconected: " << socket->getRemoteAddress().toString();
                });
        });

    if (SM->ConnectToServer(ip,port))
    {

        SM->StartLoop();
    }
}


void RunServer()
{
    //std::cout << "Server";

    //Chat* chat = Chat::Server(port);

    SocketsManager* SM = new SocketsManager([](TcpSocket* socket)
        {
            std::cout << std::endl << "Socket connected: " << socket->getRemoteAddress().toString();

            socket->Subscribe(Message, [socket](Packet packet) {
                std::string message;
                packet >> message;
                std::cout << std::endl << "New Message: " << message;

                std::string response = "Pues Yo Soy El Server";
                Packet responsePacket;
                responsePacket << response;

                socket->Send(Message, responsePacket);
                });
            socket->SubscribeOnDisconnect([](TcpSocket* socket) {
                std::cout << std::endl << "Socket disconected: " << socket->getRemoteAddress().toString();
                });
        });

    if (SM->StartListener(port))
    {
        sf::IpAddress ipAddress = sf::IpAddress::getLocalAddress();
        std::cout << "Listening on Ip: " << ipAddress.toString();
        SM->StartLoop();
    }






}


void RunWindows()
{
    Window window;

    Button* bt = new Button(50, 20, "resources/QG.png");

    bt->onClick = []() {
        std::cout << std::endl << "Long Live The Queen";
        };

    window.AddButton(bt);
    window.RunWindowLoop();


   /* sf::RenderWindow windows;
    windows.create(sf::VideoMode(800, 600), "Chat");
    windows.setFramerateLimit(60);

    sf::Text label;

    sf::Font font;
    font.loadFromFile("Minecraft.ttf");

    label.setFont(font);
    label.setCharacterSize(16);
    label.setFillColor(sf::Color::White);
    label.setString("Hello World");
    label.setOrigin(0.5, 0.5);

    label.setPosition(windows.getSize().x * 0.5, windows.getSize().y * 0.5);

    while (windows.isOpen())
    {
        windows.clear(sf::Color::Black);
        windows.draw(label);
        windows.display();
    }*/
}