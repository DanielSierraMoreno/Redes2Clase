#pragma once
#include <iostream>
#include <vector>
#include "Pieces.h"

Piece::Piece()
{

}
Piece::Piece(sf::Texture* texture, Vector2D pos)
{
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

bool Piece::CheckMove(Vector2D pos)
{
	return true;
}



tower::tower(sf::Texture* texture, Vector2D pos):Piece(texture, pos)
{
}

bool tower::CheckMove(Vector2D pos)
{
	return true;
}

bishop::bishop(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}

bool bishop::CheckMove(Vector2D pos)
{
	return true;
}

queen::queen(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}

bool queen::CheckMove(Vector2D pos)
{
	return true;
}

pawn::pawn(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}

bool pawn::CheckMove(Vector2D pos)
{
	return true;
}

knight::knight(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}

bool knight::CheckMove(Vector2D pos)
{
	return true;
}

king::king(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}

bool king::CheckMove(Vector2D pos)
{
	return true;
}
