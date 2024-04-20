#include "Pawn.h"
#include "Board.h"
Pawn::Pawn(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}
std::vector<Vector2D> Pawn::GetPosiblesMoves(Vector2D ArrayIndex, Board* board, PieceColor current)
{
	int direction = GetColor();
	posibleMoves.clear();

	//Attaque peon
	std::vector<Vector2D> additionalMoves = board->FilterEnemyTiles(GetPosiblesAttackMoves(ArrayIndex,board,current),current);
	posibleMoves.insert(posibleMoves.end(), additionalMoves.begin(), additionalMoves.end());

	//Movimiento base
	if (!alreadyMoved)
	{
		additionalMoves = board->FilterEmpty(board->GetPositionsFromDirection(ArrayIndex, current, Vector2D::Up() * direction, range + additionalFirstMoveRange));
		posibleMoves.insert(posibleMoves.end(), additionalMoves.begin(), additionalMoves.end());
	}
	else
	{
		additionalMoves = board->FilterEmpty(board->GetPositionsFromDirection(ArrayIndex, current, Vector2D::Up() * direction, range));
		posibleMoves.insert(posibleMoves.end(), additionalMoves.begin(), additionalMoves.end());
	}

	return posibleMoves;
}

std::vector<Vector2D> Pawn::GetPosiblesAttackMoves(Vector2D ArrayIndex, Board* board, PieceColor current)
{
	std::vector<Vector2D> movements;
	int direction = -GetColor();
	std::vector<Vector2D> additionalMoves = board->GetPositionsFromDirection(ArrayIndex, current, Vector2D::UpRight() * direction, attackRange);
	movements.insert(movements.end(), additionalMoves.begin(), additionalMoves.end());
	additionalMoves = board->GetPositionsFromDirection(ArrayIndex, current, Vector2D::UpLeft() * direction, attackRange);
	movements.insert(movements.end(), additionalMoves.begin(), additionalMoves.end());

	return movements;
}