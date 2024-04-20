#include "King.h"
#include "Board.h"

King::King(sf::Texture* texture, Vector2D pos) :Piece(texture, pos) 
{
	movements = { Vector2D::Up() ,Vector2D::UpRight() ,Vector2D::Down(),Vector2D::DownLeft(),Vector2D::DownRight(),Vector2D::UpLeft(), Vector2D::Left(),Vector2D::Right() };
}
std::vector<Vector2D> King::GetPosiblesMoves(Vector2D ArrayIndex, Board* board, PieceColor current)
{
	posibleMoves.clear();
	std::vector<Vector2D> FinalMoves;
	std::vector<Vector2D> noPosibleMoves = board->GetEnemyPosibleMovements(current);
	for (Vector2D move : movements)
	{
		std::vector<Vector2D> additionalMoves = board->GetPositionsFromDirection(ArrayIndex, current, move, range);
		posibleMoves.insert(posibleMoves.end(), additionalMoves.begin(), additionalMoves.end());
	}
	for (const Vector2D& posibleMoveIndex : posibleMoves)
	{
		if (std::find(noPosibleMoves.begin(), noPosibleMoves.end(), posibleMoveIndex) == noPosibleMoves.end())
		{
			FinalMoves.push_back(posibleMoveIndex);
		}
	}
	posibleMoves = FinalMoves;
	return posibleMoves;
}
std::vector<Vector2D> King::GetPosiblesMovesFake(Vector2D ArrayIndex, Board* board, PieceColor current)
{
	posibleMoves.clear();
	for (Vector2D move : movements)
	{
		std::vector<Vector2D> additionalMoves = board->GetPositionsFromDirection(ArrayIndex, current, move, range);
		posibleMoves.insert(posibleMoves.end(), additionalMoves.begin(), additionalMoves.end());
	}
	return posibleMoves;
}