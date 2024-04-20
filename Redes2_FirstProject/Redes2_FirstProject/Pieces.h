#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector2.h"

enum PieceColor {
	WHITE = -1,
	BLACK = 1,
	NONE = 2
};


enum PieceType {
	pawn = 1,
	knight = 2,
	bishop = 3,
	tower = 4,
	queen = 5,
	king = 6,
	None = 0
};
class Board;
class Player
{
public:
	PieceColor playerColor;
	bool jaque;
	bool jaqueMate;
	Player(PieceColor playerColor) { this->playerColor = playerColor; jaque = false; jaqueMate = false; }
};



class Piece : public sf::Sprite
{
private:
	Vector2D pos;
	PieceColor color;
protected:
	std::vector<Vector2D> movements;
	int range = 8;
public:
	std::vector<Vector2D> posibleMoves;

	bool alreadyMoved;
	Piece();
	Piece(sf::Texture* texture, Vector2D pos);
	void SetPosition(Vector2D pos);
	void SetPiece(sf::IntRect region, PieceColor color);
	Vector2D GetPos();
	PieceColor GetColor();
	bool CheckBounds(unsigned int x, unsigned int y);
	virtual std::vector<Vector2D> GetPosiblesMoves(Vector2D ArrayIndex, Board* board, PieceColor current);
	bool CheckMove(Vector2D pos);

};
