#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Pieces.h"

#include <map>
#include <list>



enum PieceType {
    Pawn = 1,
    Knight = 2,
    Bishop = 3,
    Tower = 4,
    Queen = 5,
    King = 6,
    None = 0
};

class Casilla : public sf::Sprite
{
public:
    Vector2D pos;
    Piece* piece;
    PieceType type;
    Vector2D boardPos;

    Casilla(Vector2D pos, Piece* piece, PieceType type, Vector2D boardPos);

};

class Board {
private:
    const float WIDTH = 1450;
    const float HEIGTH = 850;
    std::map<Vector2D, Casilla*> boardTiles;

    sf::Sprite board;

    sf::Texture* texturesPiece;
    sf::Texture* textureBoard;

    Vector2D posPressed;
    Casilla* pressedTile;
public:
    Board();
    void TrySelectPiece(sf::Vector2f worldPos);
    void TryReleasePiece(sf::Vector2f worldPos);
    void run();
    Piece* GetEmptyPiece(Vector2D pixelPos);

};
