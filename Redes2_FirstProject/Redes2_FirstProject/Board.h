#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Pieces.h"
#include <map>
#include <list>
#include "tile.h"
#include "Screen.h"
#include <string>
#include <vector>
#include "Address.h"
#include "Codable.h"



class Board :public Screen{
private:
    const float WIDTH = 1450;
    const float HEIGTH = 850;
    const float startingPosX = 9, startingPosY = 9;
    const float tileSize = 84;

public:
    std::map<Vector2D, Tile*> boardTiles;

    sf::Sprite board;

    sf::Texture* texturesPiece;
    sf::Texture* textureBoard;

    Vector2D posPressed;
    Tile* pickedPieceTile;
    std::vector<Player*> players;
    Player* currentPlayer;

    Board(int W, int H, std::string name);
    void TrySelectPiece(Vector2D boardIndex);
    void TryReleasePiece(Vector2D releaseBoardIndex);
    Piece* GetEmptyPiece(Vector2D pixelPos);
    void PosibleMoves(std::vector<Vector2D> moves);
    void ResetPosibleMoves();
    std::vector<Vector2D> GetEnemyPosibleMovements(PieceColor current);
    void CheckJaque(PieceColor current);
    std::vector<Vector2D> GetPositionsFromDirection(Vector2D arrayIndex, PieceColor pieceColor, Vector2D dir, int range);
    Vector2D GetPositionTeleport(Vector2D arrayIndex, PieceColor pieceColor ,Vector2D dir);
    bool CanMoveToTile(Tile* tile, PieceColor color);
    bool IsTileEmpty(Tile* tile);
    bool IsTileEnemy(Tile* tile, PieceColor color);
    bool IsTileAlly(Tile* tile, PieceColor color);
    bool IsValidIndex(Vector2D arrayIndex);
    Vector2D WorldPosToBoard(Vector2D worldPos);
    Vector2D BoardToWorldPos(Vector2D boardPos);
    std::vector<Vector2D> FilterEnemyTiles(std::vector<Vector2D> tiles, PieceColor color);
    std::vector<Vector2D> FilterEmpty(std::vector<Vector2D> tiles);

};



class RoomInfo : public ICodable
{
public:
    RoomInfo() = default;
    RoomInfo(Packet& p) {
        Decode(p);
    }

    void Code(sf::Packet& packet) override {
        packet << playersNames << spectatorsNames;

    }
    void Decode(sf::Packet& packet) override {
        packet >> playersNames >> spectatorsNames;

    }
    CPVector<CPString> playersNames;
    CPVector<CPString> spectatorsNames;

};

class RoomsInfo : public ICodable
{
public:
    RoomsInfo() = default;
    RoomsInfo(Packet& p) {
        Decode(p);
    }





    void Code(sf::Packet& packet) override {
        packet << roomsInfo;

    }
    void Decode(sf::Packet& packet) override {
        packet >> roomsInfo;

    }
    CPVector<RoomInfo> roomsInfo;

};


class EnterRoom : public ICodable
{
public:
    EnterRoom() = default;
    EnterRoom(Packet& p) {
        Decode(p);
    }
    EnterRoom(std::string name, int id) {
        this->name = name;
        this->id = id;
    };

    std::string name;
    int id;



    void Code(sf::Packet& packet) override {
        packet << name << id;

    }
    void Decode(sf::Packet& packet) override {
        packet >> name >> id;

    }
};
