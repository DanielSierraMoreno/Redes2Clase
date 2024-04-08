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
	Pawn = 1,
	Knight = 2,
	Bishop = 3,
	Tower = 4,
	Queen = 5,
	King = 6,
	None = 0
};
class Piece;

class Board;
class Player
{
public:
	PieceColor playerColor;
	bool jaque;
	bool jaqueMate;
	Player(PieceColor playerColor) { this->playerColor = playerColor; jaque = false; jaqueMate = false; }
};

class Casilla : public sf::Sprite
{
public:
	Vector2D pos;
	Piece* piece;
	PieceType type;
	Vector2D boardPos;
	sf::RectangleShape* marca;
	Casilla(Vector2D pos, Piece* piece, PieceType type, Vector2D boardPos);

};

class Piece : public sf::Sprite
{
private:
	Vector2D pos;
	PieceColor color;
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
	virtual std::vector<Vector2D> GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current);
	bool CheckMove(Vector2D pos);

};


class king: public Piece
{
private:

public:
	king();
	king(sf::Texture* texture, Vector2D pos);
	virtual std::vector<Vector2D> GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current) override;
	std::vector<Vector2D> GetPosiblesMovesFake(Vector2D currentPos, Board board, PieceColor current);


};


class knight : public Piece
{
private:


public:
	knight(sf::Texture* texture, Vector2D pos);
	virtual std::vector<Vector2D> GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current) override;

};

class pawn : public Piece
{
private:


public:
	pawn(sf::Texture* texture, Vector2D pos);
	virtual std::vector<Vector2D> GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current) override;
	std::vector<Vector2D> GetPosiblesMovesFake(Vector2D currentPos, Board board, PieceColor current);

};

class queen : public Piece
{
private:


public:
	queen(sf::Texture* texture, Vector2D pos);
	virtual std::vector<Vector2D> GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current) override;


};


class tower : public Piece
{
private:


public:
	tower(sf::Texture* texture, Vector2D pos);
	virtual std::vector<Vector2D> GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current) override;


};

class bishop : public Piece
{
private:


public:
	bishop(sf::Texture* texture, Vector2D pos);
	virtual std::vector<Vector2D> GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current) override;

};


