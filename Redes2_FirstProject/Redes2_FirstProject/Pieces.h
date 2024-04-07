#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector2.h"

enum PieceColor {
	WHITE = 0,
	BLACK = 1,
	NONE = 2
};




class Piece : public sf::Sprite
{
private:
	Vector2D pos;
	PieceColor color;
public:

	Piece();
	Piece(sf::Texture* texture, Vector2D pos);
	void SetPosition(Vector2D pos);
	void SetPiece(sf::IntRect region, PieceColor color);
	Vector2D GetPos();
	PieceColor GetColor();
	bool CheckBounds(unsigned int x, unsigned int y);
	std::vector<Vector2D> GetPosiblesMoves();
	virtual bool CheckMove(Vector2D pos);

};


class king: public Piece
{
private:

public:
	king(sf::Texture* texture, Vector2D pos);
	virtual bool CheckMove(Vector2D pos) override;


};


class knight : public Piece
{
private:


public:
	knight(sf::Texture* texture, Vector2D pos);
	virtual bool CheckMove(Vector2D pos) override;

};

class pawn : public Piece
{
private:


public:
	pawn(sf::Texture* texture, Vector2D pos);
	virtual bool CheckMove(Vector2D pos) override;

};

class queen : public Piece
{
private:


public:
	queen(sf::Texture* texture, Vector2D pos);
	virtual bool CheckMove(Vector2D pos) override;


};


class tower : public Piece
{
private:


public:
	tower(sf::Texture* texture, Vector2D pos);
	virtual bool CheckMove(Vector2D pos) override;


};

class bishop : public Piece
{
private:


public:
	bishop(sf::Texture* texture, Vector2D pos);
	virtual bool CheckMove(Vector2D pos) override;

};


