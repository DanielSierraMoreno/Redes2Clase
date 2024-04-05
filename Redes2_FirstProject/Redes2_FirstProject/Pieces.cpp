#pragma once
#include <iostream>
#include <vector>
#include "Pieces.h"

Piece::Piece(sf::Texture* texture)
{

	this->setTexture(*texture);
}
Piece::Piece(sf::Texture* texture, Vector2D pos)
{
	this->setTexture(*texture);
	this->pos = pos;
	this->setPosition(pos.x, pos.y);

}
void Piece::SetPosition(Vector2D pos)
{

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

bool Piece::CheckBounds(unsigned int x, unsigned int y)
{
	return this->getGlobalBounds().contains(x, y);
}

tower::tower(sf::Texture* texture, Vector2D pos):Piece(texture, pos)
{
}

bishop::bishop(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}

queen::queen(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}

pawn::pawn(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}

knight::knight(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}

king::king(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}
