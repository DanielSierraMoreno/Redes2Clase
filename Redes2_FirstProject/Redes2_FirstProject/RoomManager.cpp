#include "RoomManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
RoomManager::RoomManager()
{
}
void RoomManager::Init()
{
    std::cout << "Client";

    std::cout << std::endl << "Set server IP --> ";

    std::string ip;
    std::getline(std::cin, ip);

}
