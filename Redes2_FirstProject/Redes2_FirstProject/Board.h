#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Pieces.h"

#include <map>
#include <list>





class Board {
private:
    const float WIDTH = 1450;
    const float HEIGTH = 850;

public:
    std::map<Vector2D, Casilla*> boardTiles;

    sf::Sprite board;

    sf::Texture* texturesPiece;
    sf::Texture* textureBoard;

    Vector2D posPressed;
    Casilla* pressedTile;
    std::vector<Player*> players;
    Player* currentPlayer;
    Board();
    void TrySelectPiece(sf::Vector2f worldPos);
    void TryReleasePiece(sf::Vector2f worldPos);
    void run();
    Piece* GetEmptyPiece(Vector2D pixelPos);
    void PosibleMoves(std::vector<Vector2D> moves);
    void ResetPosibleMoves();
    std::vector<Vector2D> GetEnemyPosibleMovements(PieceColor current);
    void CheckJaque(PieceColor current);

};
