#pragma once
#include <iostream>
#include <vector>
#include "Pieces.h"
#include "Board.h"

Piece::Piece()
{

}
Piece::Piece(sf::Texture* texture, Vector2D pos)
{
	alreadyMoved = false;
	this->setTexture(*texture);
	this->pos = pos;
	this->setPosition(pos.x, pos.y);
}
void Piece::SetPosition(Vector2D pos)
{
	this->pos = pos;

	this->setPosition(pos.x, pos.y);

}

void Piece::SetPiece(sf::IntRect region, PieceColor color)
{
	this->color = color;
	this->setTextureRect(region);
}

Vector2D Piece::GetPos()
{
	return pos;
}

PieceColor Piece::GetColor()
{
	return color;
}

bool Piece::CheckBounds(unsigned int x, unsigned int y)
{
	return this->getGlobalBounds().contains(x, y);
}

std::vector<Vector2D> Piece::GetPosiblesMoves(Vector2D ArrayIndex, Board board, PieceColor current)
{
	posibleMoves.clear();
	for (Vector2D move : movements)
	{
		std::vector<Vector2D> additionalMoves = board.GetPositionsFromDirection(ArrayIndex, current, move, range);
		posibleMoves.insert(posibleMoves.end(), additionalMoves.begin(), additionalMoves.end());
	}

	return posibleMoves;
}

bool Piece::CheckMove(Vector2D pos)
{
	for (Vector2D& move : posibleMoves) {
		if (move.x == pos.x && move.y == pos.y) {
			return true;
		}
	}
	return false;
}
