#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Pieces.h"
class Board;
class King : public Piece
{
private:
	int range = 1;
public:
	King();
	King(sf::Texture* texture, Vector2D pos);
	virtual std::vector<Vector2D> GetPosiblesMoves(Vector2D ArrayIndex, Board* board, PieceColor current);
	std::vector<Vector2D> GetPosiblesMovesFake(Vector2D currentPos, Board* board, PieceColor current);
};
