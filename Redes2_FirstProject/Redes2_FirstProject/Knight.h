#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Pieces.h"
class Board;
class Knight : public Piece
{
private:

public:
	Knight(sf::Texture* texture, Vector2D pos);
};
