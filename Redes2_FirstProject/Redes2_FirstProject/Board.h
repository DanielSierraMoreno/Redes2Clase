#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Pieces.h"
#include <map>
#include <list>
#include "tile.h"




class Board {
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
    Board();
    void TrySelectPiece(Vector2D boardIndex);
    void TryReleasePiece(Vector2D releaseBoardIndex);
    void run();
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
