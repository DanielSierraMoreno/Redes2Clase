#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Pieces.h"
class Board;
class Pawn : public Piece
{
private:
	int attackRange = 1;
	int additionalFirstMoveRange = 1;
	int range = 1;

public:
	Pawn(sf::Texture* texture, Vector2D pos);
	virtual std::vector<Vector2D> GetPosiblesMoves(Vector2D ArrayIndex, Board* board, PieceColor current);
	std::vector<Vector2D> GetPosiblesAttackMoves(Vector2D ArrayIndex, Board* board, PieceColor current);

};

