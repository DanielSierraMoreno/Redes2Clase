#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Pieces.h"
class Board;
class Queen : public Piece
{
private:

public:
	Queen(sf::Texture* texture, Vector2D pos);

};
