#pragma once
#include <iostream>
#include <vector>
#include "Pieces.h"
#include "Board.h"

Piece::Piece()
{

}
Piece::Piece(sf::Texture* texture, Vector2D pos)
{
	alreadyMoved = false;
	this->setTexture(*texture);
	this->pos = pos;
	this->setPosition(pos.x, pos.y);
}
void Piece::SetPosition(Vector2D pos)
{
	this->pos = pos;

	this->setPosition(pos.x, pos.y);

}

void Piece::SetPiece(sf::IntRect region, PieceColor color)
{

	this->color = color;
	this->setTextureRect(region);
}

Vector2D Piece::GetPos()
{
	return pos;
}

PieceColor Piece::GetColor()
{
	return color;
}

bool Piece::CheckBounds(unsigned int x, unsigned int y)
{
	return this->getGlobalBounds().contains(x, y);
}

std::vector<Vector2D> Piece::GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current)
{

	return std::vector<Vector2D>();
}

bool Piece::CheckMove(Vector2D pos)
{
	for (Vector2D& move : posibleMoves) {
		if (move.x == pos.x && move.y == pos.y) {
			return true;
		}
	}
	return false;
}



tower::tower(sf::Texture* texture, Vector2D pos):Piece(texture, pos)
{
}


std::vector<Vector2D> tower::GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current)
{
	std::vector<Vector2D> list;
	
	for (int i = 0; i < 4; i++)
	{
		int pos = 0;
		switch (i)
		{
			case 0:
				 pos = currentPos.x;

				while (pos >= 1)
				{
					pos--;
					if (board.boardTiles[Vector2D(pos, currentPos.y)]->piece->GetColor() == current)
					{
						break;
					}
					else if (board.boardTiles[Vector2D(pos, currentPos.y)]->piece->GetColor() == -current)
					{
						list.push_back(Vector2D(pos, currentPos.y));

						break;

					}
					else
					{
						list.push_back(Vector2D(pos, currentPos.y));

					}

				} 

				break;
			case 1:
				 pos = currentPos.x;

				while (pos <= 6)
				{
					pos++;
					if (board.boardTiles[Vector2D(pos, currentPos.y)]->piece->GetColor() == current)
					{
						break;
					}
					else if (board.boardTiles[Vector2D(pos, currentPos.y)]->piece->GetColor() == -current)
					{
						list.push_back(Vector2D(pos, currentPos.y));

						break;

					}
					else
					{
						list.push_back(Vector2D(pos, currentPos.y));

					}

				} 
				break;
			case 2:
				 pos = currentPos.y;

				while (pos >= 1)
				{
					pos--;
					if (board.boardTiles[Vector2D(currentPos.x, pos)]->piece->GetColor() == current)
					{
						break;
					}
					else if (board.boardTiles[Vector2D(currentPos.x, pos)]->piece->GetColor() == -current)
					{
						list.push_back(Vector2D(currentPos.x, pos));

						break;

					}
					else
					{
						list.push_back(Vector2D(currentPos.x, pos));

					}

				} 
				break;
			case 3:
				 pos = currentPos.y;

				while (pos <= 6)
				{
					pos++;
					if (board.boardTiles[Vector2D(currentPos.x, pos)]->piece->GetColor() == current)
					{
						break;
					}
					else if (board.boardTiles[Vector2D(currentPos.x, pos)]->piece->GetColor() == -current)
					{
						list.push_back(Vector2D(currentPos.x, pos));

						break;

					}
					else
					{
						list.push_back(Vector2D(currentPos.x, pos));

					}

				} 
				break;
		}
	}

	posibleMoves = list;

	return list;
}

bishop::bishop(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}



std::vector<Vector2D> bishop::GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current)
{

	std::vector<Vector2D> list;

	for (int i = 0; i < 4; i++)
	{
		int posX = currentPos.x;
		int posY = currentPos.y;

		switch (i)
		{
		case 0:


			while (posX >= 1 && posY >= 1)
			{
				posX--;
				posY--;

				if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == current)
				{
					break;
				}
				else if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == -current)
				{
					list.push_back(Vector2D(posX, posY));

					break;

				}
				else
				{
					list.push_back(Vector2D(posX, posY));

				}

			}

			break;
		case 1:


			while (posX >= 1 && posY <= 6)
			{
				posX--;
				posY++;

				if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == current)
				{
					break;
				}
				else if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == -current)
				{
					list.push_back(Vector2D(posX, posY));

					break;

				}
				else
				{
					list.push_back(Vector2D(posX, posY));

				}

			}
			break;
		case 2:


			while (posX <= 6 && posY >= 1)
			{
				posX++;
				posY--;

				if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == current)
				{
					break;
				}
				else if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == -current)
				{
					list.push_back(Vector2D(posX, posY));

					break;

				}
				else
				{
					list.push_back(Vector2D(posX, posY));

				}

			}
			break;
		case 3:


			while (posX <= 6 && posY <= 6)
			{
				posX++;
				posY++;

				if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == current)
				{
					break;
				}
				else if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == -current)
				{
					list.push_back(Vector2D(posX, posY));

					break;

				}
				else
				{
					list.push_back(Vector2D(posX, posY));

				}

			}
			break;
		}
	}

	posibleMoves = list;

	return list;
}

queen::queen(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}
std::vector<Vector2D> queen::GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current)
{
	std::vector<Vector2D> list;
	for (int i = 0; i < 4; i++)
	{
		int pos = 0;
		switch (i)
		{
		case 0:
			pos = currentPos.x;

			while (pos >= 1)
			{
				pos--;
				if (board.boardTiles[Vector2D(pos, currentPos.y)]->piece->GetColor() == current)
				{
					break;
				}
				else if (board.boardTiles[Vector2D(pos, currentPos.y)]->piece->GetColor() == -current)
				{
					list.push_back(Vector2D(pos, currentPos.y));

					break;

				}
				else
				{
					list.push_back(Vector2D(pos, currentPos.y));

				}

			}

			break;
		case 1:
			pos = currentPos.x;

			while (pos <= 6)
			{
				pos++;
				if (board.boardTiles[Vector2D(pos, currentPos.y)]->piece->GetColor() == current)
				{
					break;
				}
				else if (board.boardTiles[Vector2D(pos, currentPos.y)]->piece->GetColor() == -current)
				{
					list.push_back(Vector2D(pos, currentPos.y));

					break;

				}
				else
				{
					list.push_back(Vector2D(pos, currentPos.y));

				}

			}
			break;
		case 2:
			pos = currentPos.y;

			while (pos >= 1)
			{
				pos--;
				if (board.boardTiles[Vector2D(currentPos.x, pos)]->piece->GetColor() == current)
				{
					break;
				}
				else if (board.boardTiles[Vector2D(currentPos.x, pos)]->piece->GetColor() == -current)
				{
					list.push_back(Vector2D(currentPos.x, pos));

					break;

				}
				else
				{
					list.push_back(Vector2D(currentPos.x, pos));

				}

			}
			break;
		case 3:
			pos = currentPos.y;

			while (pos <= 6)
			{
				pos++;
				if (board.boardTiles[Vector2D(currentPos.x, pos)]->piece->GetColor() == current)
				{
					break;
				}
				else if (board.boardTiles[Vector2D(currentPos.x, pos)]->piece->GetColor() == -current)
				{
					list.push_back(Vector2D(currentPos.x, pos));

					break;

				}
				else
				{
					list.push_back(Vector2D(currentPos.x, pos));

				}

			}
			break;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		int posX = currentPos.x;
		int posY = currentPos.y;

		switch (i)
		{
		case 0:


			while (posX >= 1 && posY >= 1)
			{
				posX--;
				posY--;

				if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == current)
				{
					break;
				}
				else if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == -current)
				{
					list.push_back(Vector2D(posX, posY));

					break;

				}
				else
				{
					list.push_back(Vector2D(posX, posY));

				}

			}

			break;
		case 1:


			while (posX >= 1 && posY <= 6)
			{
				posX--;
				posY++;

				if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == current)
				{
					break;
				}
				else if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == -current)
				{
					list.push_back(Vector2D(posX, posY));

					break;

				}
				else
				{
					list.push_back(Vector2D(posX, posY));

				}

			}
			break;
		case 2:


			while (posX <= 6 && posY >= 1)
			{
				posX++;
				posY--;

				if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == current)
				{
					break;
				}
				else if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == -current)
				{
					list.push_back(Vector2D(posX, posY));

					break;

				}
				else
				{
					list.push_back(Vector2D(posX, posY));

				}

			}
			break;
		case 3:


			while (posX <= 6 && posY <= 6)
			{
				posX++;
				posY++;

				if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == current)
				{
					break;
				}
				else if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == -current)
				{
					list.push_back(Vector2D(posX, posY));

					break;

				}
				else
				{
					list.push_back(Vector2D(posX, posY));

				}

			}
			break;
		}
	}

	posibleMoves = list;

	return list;
}

pawn::pawn(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}


std::vector<Vector2D> pawn::GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current)
{
	std::vector<Vector2D> list;

	int limite = 0;
	int direction = 0;

	if (GetColor() == WHITE)
	{
		limite = 8;
		direction = 1;
	}
	else
	{
		limite = -1;
		direction = -1;
	}

	int posX = currentPos.x + direction;
	if (posX != limite)
	{
		for (int i = -1; i < 2;i++)
		{
			int posY = currentPos.y + i;

			if (posY != -1 && posY != 8)
			{
				if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == -current && i != 0)
				{
					list.push_back(Vector2D(posX, posY));


				}
				else if(i == 0 && board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == NONE)
				{
					list.push_back(Vector2D(posX, posY));

				}


			}


		}
	}

	if (!alreadyMoved)
	{
		int posX = currentPos.x + (direction * 2);
		if (posX != limite)
		{
	
				int posY = currentPos.y;

		
				if (board.boardTiles[Vector2D(posX - direction, posY)]->piece->GetColor() == -current || board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == -current || board.boardTiles[Vector2D(posX - direction, posY)]->piece->GetColor() == current || board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == current)
				{

				}
				else
				{
					list.push_back(Vector2D(posX, posY));

				}


				


			
		}
	}
	posibleMoves = list;

	return list;
}

std::vector<Vector2D> pawn::GetPosiblesAttackMoves(Vector2D currentPos, Board board, PieceColor current)
{

	std::vector<Vector2D> list;

	int limite = 0;
	int direction = 0;

	if (GetColor() == WHITE)
	{
		limite = 8;
		direction = 1;
	}
	else
	{
		limite = -1;
		direction = -1;
	}

	int posX = currentPos.x + direction;
	if (posX != limite)
	{
		for (int i = -1; i < 2;i++)
		{
			int posY = currentPos.y + i;

			if (posY != -1 && posY != 8)
			{
				if (i != 0)
				{
					list.push_back(Vector2D(posX, posY));


				}
				else if (i == 0 && board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == NONE)
				{

				}


			}


		}
	}

	posibleMoves = list;

	return list;
}

knight::knight(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}



std::vector<Vector2D> knight::GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current)
{

	std::vector<Vector2D> list;

	for (int i = 0; i < 4; i++)
	{
		int posX = 0;
		int posY = 0;

		switch (i)
		{
		case 0:
			posX = currentPos.x-2;
			posY = currentPos.y;
			for (int i = -1; i < 2 && posX >= 0;i += 2)
			{
				if (posY + i >= 0 && posY + i <= 7)
				{

					if (board.boardTiles[Vector2D(posX, posY + i)]->piece->GetColor() != current)
					{
						list.push_back(Vector2D(posX, posY + i));

					}
				}
			}
			

			break;
		case 1:
			posX = currentPos.x + 2;
			posY = currentPos.y;
			for (int i = -1; i < 2 && posX <= 7;i += 2)
			{
				if (posY + i >= 0 && posY + i <= 7)
				{

					if (board.boardTiles[Vector2D(posX, posY + i)]->piece->GetColor() != current)
					{
						list.push_back(Vector2D(posX, posY + i));

					}
				}
			}
			break;
		case 2:
			posX = currentPos.x;
			posY = currentPos.y - 2;
			for (int i = -1; i < 2 && posY >= 0;i += 2)
			{
				if (posX + i >= 0 && posX + i <= 7)
				{
					if (board.boardTiles[Vector2D(posX + i, posY)]->piece->GetColor() != current)
					{
						list.push_back(Vector2D(posX + i, posY));

					}
				}
			}
			break;
		case 3:
			posX = currentPos.x;
			posY = currentPos.y + 2;
			for (int i = -1; i < 2 && posY <= 7;i += 2)
			{
				if (posX + i >= 0 && posX + i <= 7)
				{

					if (board.boardTiles[Vector2D(posX + i, posY)]->piece->GetColor() != current)
					{
						list.push_back(Vector2D(posX + i, posY));

					}
				}
			}
			break;
		}
	}

	posibleMoves = list;

	return list;
}

king::king(sf::Texture* texture, Vector2D pos) :Piece(texture, pos)
{
}


std::vector<Vector2D> king::GetPosiblesMoves(Vector2D currentPos, Board board, PieceColor current)
{
	std::vector<Vector2D> list;
	std::vector<Vector2D> noPosibleMoves = board.GetEnemyPosibleMovements(current);

	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			int posX = currentPos.x + x;
			int posY = currentPos.y + y;

			if (std::find(noPosibleMoves.begin(), noPosibleMoves.end(), Vector2D(posX, posY)) == noPosibleMoves.end()) {
				
					if (posX != -1 && posX != 8 && posY != -1 && posY != 8)
					{
						if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == current || board.boardTiles[Vector2D(posX, posY)]->type == King)
						{
						}
						else if (board.boardTiles[Vector2D(posX, posY)]->piece->GetColor() == -current)
						{

							list.push_back(Vector2D(posX, posY));


						}
						else
						{
							list.push_back(Vector2D(posX, posY));

						}

					}
				}
			}
	}



	posibleMoves = list;

	return list;
}

std::vector<Vector2D> king::GetPosiblesMovesFake(Vector2D currentPos, Board board, PieceColor current)
{
	std::vector<Vector2D> list;

	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			int posX = currentPos.x + x;
			int posY = currentPos.y + y;

			if (posX != -1 && posX != 8 && posY != -1 && posY != 8)
			{
				if (board.boardTiles[Vector2D(posX, posY)]->type == King)
				{
				}
				else
				{
					list.push_back(Vector2D(posX, posY));

				}

			}

		}
	}



	posibleMoves = list;

	return list;
}
