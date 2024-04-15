#include "Queen.h"

Queen::Queen(sf::Texture* texture, Vector2D pos) : Piece(texture, pos)
{
	movements = { Vector2D::Up() ,Vector2D::UpRight() ,Vector2D::Down(),Vector2D::DownLeft(),Vector2D::DownRight(),Vector2D::UpLeft(), Vector2D::Left(),Vector2D::Right() };
}
