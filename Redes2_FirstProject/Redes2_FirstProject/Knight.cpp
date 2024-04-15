#include "Knight.h"

Knight::Knight(sf::Texture* texture, Vector2D pos) : Piece(texture, pos)
{
	range = 1;
	movements = {
	 {1, 2}, {2, 1}, {1, -2}, {2, -1},
	 {-1, 2}, {-2, 1}, {-1, -2}, {-2, -1} };
}
