#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Pieces.h"
class Tile : public sf::Sprite
{
public:
	Vector2D pos;
	Piece* piece;
	PieceType type;
	sf::RectangleShape* marca;
	Tile(Vector2D pos, Piece* piece, PieceType type);
};