#include "tile.h"

Tile::Tile(Vector2D pos, Piece* piece, PieceType type)
{
    this->pos = pos;

    marca = new sf::RectangleShape(sf::Vector2f(64, 64));
    marca->setFillColor(sf::Color(0, 255, 0, 0));
    marca->setPosition(pos.x, pos.y);

    this->piece = piece;
    this->type = type;
}
