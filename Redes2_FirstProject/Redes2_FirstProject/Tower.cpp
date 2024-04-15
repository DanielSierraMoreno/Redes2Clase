#include "Tower.h"

Tower::Tower(sf::Texture* texture, Vector2D pos) : Piece(texture, pos)
{
	movements = { Vector2D::Up() ,Vector2D::Down(), Vector2D::Left(),Vector2D::Right() };
}
