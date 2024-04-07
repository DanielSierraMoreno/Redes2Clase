// Redes2_FirstProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include "ConsoleControl.h"
#include <SFML/Network.hpp>
#include "Chat.h"
#include <SFML/Graphics.hpp>
#include "Board.h"

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
    Board board;

    //RunWindows();
    board.run();

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
        RunServer(); //Iniciem server
        break;
    case 'C':
    case 'c':
        RunClient(); //Iniciem Client

        break;
    default:
        break;
    }

    while (true)
    {

    }

}
void RunClient() 
{
    std::cout << "Client";

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
}


void RunServer()
{
    //std::cout << "Server";

    Chat* chat = Chat::Server(port);
    return;
    SocketsManager* SM = new SocketsManager([](TcpSocket* socket)//Al crear un SocketsManager hem de passar una funcio lambda al constructor
        {                                                         //que es guardara a una variable privada de la clase
                                                                  //per tal que quan es conecti un TcpSocket pasarlo com a parametre. 
                                                                  //(veure SocketsManager::AddSocket(TcpSocket* socket) per entendreho)
                                                                  //Per tant, tots els sockets que conectem implementaran la funcionalitat seguent:

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
            socket->SubscribeOnDisconnect([](TcpSocket* socket) {//El TcpSocket que passem com a parametre te una variable list de lambdas a executar quan es desconecti.
                                                                 //En aquest cas passem una lambda que fa un print del TcpSocket que sha desconectat

                std::cout << std::endl << "Socket disconected: " << socket->getRemoteAddress().toString();
            });




        });

    if (SM->StartListener(port)) //Intentarem començar a escoltar amb el listener del servidor
    {
        sf::IpAddress ipAddress = sf::IpAddress::getLocalAddress();
        std::cout << "Listening on Ip: " << ipAddress.toString();
        SM->StartLoop(); //Si ho aconseguim començarem el bucle d'execucio 
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