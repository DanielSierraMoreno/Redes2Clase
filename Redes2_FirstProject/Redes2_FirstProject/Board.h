#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Pieces.h"

#include <map>
#include <list>



enum PieceType {
    PawnWhite = 1,
    KnightWhite = 2,
    BishopWhite = 3,
    TowerWhite = 4,
    QueenWhite = 5,
    KingWhite = 6,
    PawnBlack = -1,
    KnightBlack = -2,
    BishopBlack = -3,
    TowerBlack = -4,
    QueenBlack = -5,
    KingBlack = -6,
    None = 0
};

class Board {
private:
    const float WIDTH = 1450;
    const float HEIGTH = 850;
    std::map<Vector2D, Piece*> pieces;
    std::map<Vector2D, Vector2D> boardPos;
    std::map<Vector2D, PieceType> boardPieces;
    sf::Sprite board;

    sf::Texture* texturesPiece;
    sf::Texture* textureBoard;

    Vector2D posPressed;
    Piece* pressedPiece;
public:
    Board();
    void UpdateBoard();

    void run();

};
