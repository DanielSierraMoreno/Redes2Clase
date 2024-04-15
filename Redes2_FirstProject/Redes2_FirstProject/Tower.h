#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Pieces.h"
class Board;
class Tower : public Piece
{
private:

public:
	Tower(sf::Texture* texture, Vector2D pos);

};
