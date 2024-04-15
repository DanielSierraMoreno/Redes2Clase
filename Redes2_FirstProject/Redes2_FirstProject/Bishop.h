#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Pieces.h"
class Board;
class Bishop : public Piece
{
private:

public:
	Bishop(sf::Texture* texture, Vector2D pos);

};
