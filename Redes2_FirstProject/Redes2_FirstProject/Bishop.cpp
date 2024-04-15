#include "Bishop.h"

Bishop::Bishop(sf::Texture* texture, Vector2D pos) : Piece(texture, pos)
{
	movements = { Vector2D::UpRight() ,Vector2D::DownLeft(),Vector2D::DownRight(),Vector2D::UpLeft() };
}
