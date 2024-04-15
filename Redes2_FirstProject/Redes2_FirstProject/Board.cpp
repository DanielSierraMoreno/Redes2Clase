#pragma once
#include "Board.h"
#include "Pieces.h"
#include "Queen.h"
#include "Knight.h"
#include "King.h"
#include "Tower.h"
#include "Pawn.h"
#include "Bishop.h"

Board::Board()
{
    players.push_back(new Player(WHITE));
    players.push_back(new Player(BLACK));
    currentPlayer = players[0];
    pickedPieceTile = nullptr;
    texturesPiece = new sf::Texture;
    if (!texturesPiece->loadFromFile("resources/Piezas.png"))
    {
        //manage Error
    }
    textureBoard = new sf::Texture;

    if (!textureBoard->loadFromFile("resources/tablero.jpg"))
    {
        //manage Error
    }
    board.setTexture(*textureBoard);
    board.setPosition(0, 0);
    board.setScale(3,3);
 
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            PieceType type;
            Piece* piece = new Piece();
            Vector2D pixelPos = BoardToWorldPos(Vector2D(x, y));
            PieceColor color = y <= 1 ? PieceColor::WHITE : PieceColor::BLACK;
            int textureYCord = y <= 1 ? 64 : 0;

            if (y == 0 || y == 7)     
                switch (x)
                {
                case 0:
                case 7:

                    type = PieceType::tower;
                    piece = new Tower(texturesPiece, pixelPos);
                    piece->SetPiece(sf::IntRect(128, textureYCord, 64, 64), color);
                    break;
                case 1:
                case 6:

                    type = PieceType::knight;
                    piece = new Knight(texturesPiece, pixelPos);

                    piece->SetPiece(sf::IntRect(192, textureYCord, 64, 64), color);
                    break;
                case 2:
                case 5:
                    type = PieceType::bishop;
                    piece = new Bishop(texturesPiece, pixelPos);
                    piece->SetPiece(sf::IntRect(256, textureYCord, 64, 64), color);
                    break;
                case 4:
                    type = PieceType::queen;
                    piece = new Queen(texturesPiece, pixelPos);
                    piece->SetPiece(sf::IntRect(64, textureYCord, 64, 64), color);
                    break;
                case 3:
                    type = PieceType::king;
                    piece = new King(texturesPiece, pixelPos);
                    piece->SetPiece(sf::IntRect(0, textureYCord, 64, 64), color);
                    break;

                default:
                    break;
                }
            else if (y == 1 || y == 6)
            {
                type = PieceType::pawn;
                piece = new Pawn(texturesPiece, pixelPos);
                piece->SetPiece(sf::IntRect(320, textureYCord, 64, 64), color);
            }
            else
            {
                type = PieceType::None;
                piece = GetEmptyPiece(pixelPos);
            }
            boardTiles.emplace(Vector2D(x,y), new Tile(pixelPos,
                piece,
                type));
        }
    }
}

Piece* Board::GetEmptyPiece(Vector2D pixelPos)
{
    Piece* piece;
    piece = new Piece(texturesPiece, pixelPos);
    piece->SetPiece(sf::IntRect(320, 0, 64, 64), NONE);
    piece->setColor(sf::Color(0, 0, 0, 0));
    return piece;
}
void Board::PosibleMoves(std::vector<Vector2D> moves)
{
    for (Vector2D& it : moves)
    {
        boardTiles[it]->marca->setFillColor(sf::Color(0, 255, 0, 64));
    }
}
void Board::ResetPosibleMoves()
{
    for (const auto& pair : boardTiles) {
        Tile* tile = pair.second;
        tile->marca->setFillColor(sf::Color(0, 255, 0, 0));
    }
}
std::vector<Vector2D> Board::GetEnemyPosibleMovements(PieceColor current)
{
    std::vector<Vector2D> list;
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            PieceColor enemyColor = boardTiles[Vector2D(x, y)]->piece->GetColor();
            if (enemyColor != -current)
                continue;
            if (boardTiles[Vector2D(x, y)]->type == king)
            {
                std::vector<Vector2D> list2;
                list2 = dynamic_cast<King*>(boardTiles[Vector2D(x, y)]->piece)->GetPosiblesMovesFake(Vector2D(x, y), *this, enemyColor);
                list.insert(list.end(), list2.begin(), list2.end());
            }
            else if (boardTiles[Vector2D(x, y)]->type == pawn)
            {
                std::vector<Vector2D> list2;
                list2 = dynamic_cast<Pawn*>(boardTiles[Vector2D(x, y)]->piece)->GetPosiblesAttackMoves(Vector2D(x, y), *this, enemyColor);
                list.insert(list.end(), list2.begin(), list2.end());
            }
            else
            {
                std::vector<Vector2D> list2;
                list2 = boardTiles[Vector2D(x, y)]->piece->GetPosiblesMoves(Vector2D(x, y), *this, enemyColor);
                list.insert(list.end(), list2.begin(), list2.end());
            }
        }
    }
    return list;
}
std::vector<Vector2D> Board::FilterEnemyTiles(std::vector<Vector2D> tiles, PieceColor color) 
{
    std::vector<Vector2D> filteredList;
    for (Vector2D tileIndex: tiles)
    {
        PieceColor tilePiececolor = boardTiles[tileIndex]->piece->GetColor();
        if (tilePiececolor == -color)
            filteredList.push_back(tileIndex);
    }
    return filteredList;
}
std::vector<Vector2D> Board::FilterEmpty(std::vector<Vector2D> tiles)
{
    std::vector<Vector2D> filteredList;
    for (Vector2D tileIndex : tiles)
    {
        if (IsTileEmpty(boardTiles[tileIndex]))
            filteredList.push_back(tileIndex);
    }
    return filteredList;
}

void Board::CheckJaque(PieceColor current)
{
    std::vector<Vector2D> list = GetEnemyPosibleMovements(current);
    Vector2D kingPos;
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (boardTiles[Vector2D(x,y)]->type == king && boardTiles[Vector2D(x,y)]->piece->GetColor() == currentPlayer->playerColor)
            {
                kingPos = Vector2D(x,y);
            }
        }
    }
    if (std::find(list.begin(), list.end(), kingPos) != list.end()) 
    {
        if(!currentPlayer->jaque)
            currentPlayer->jaque = true;
        else
            currentPlayer->jaqueMate = true;

        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                if (boardTiles[Vector2D(x, y)]->type == king && boardTiles[Vector2D(x, y)]->piece->GetColor() == currentPlayer->playerColor)
                {
                    kingPos = Vector2D(x, y);
                }
            }
        }
        boardTiles[kingPos]->marca->setFillColor(sf::Color(255, 0, 0, 64));

        if(boardTiles[kingPos]->piece->GetPosiblesMoves(kingPos, *this,currentPlayer->playerColor).size() == 0)
        {
            currentPlayer->jaqueMate = true;
        }
    }
}

std::vector<Vector2D> Board::GetPositionsFromDirection(Vector2D arrayIndex,PieceColor pieceColor,Vector2D dir, int range)
{
    std::vector<Vector2D> posibleTiles;
    for (int i = 1; i <= range; i++)
    {
        Vector2D checkIndex = arrayIndex + (dir * i);
        if (!IsValidIndex(checkIndex))
            continue;
        if (IsTileAlly(boardTiles[checkIndex], pieceColor))
        {
            return posibleTiles;
        }
        else if (IsTileEnemy(boardTiles[checkIndex], pieceColor))
        {
            posibleTiles.push_back(checkIndex);
            return posibleTiles;
        }
        else if (IsTileEmpty(boardTiles[checkIndex]))
        {
            posibleTiles.push_back(checkIndex);
        }
    }
    return posibleTiles;
}
Vector2D Board::GetPositionTeleport(Vector2D arrayIndex,PieceColor pieceColor, Vector2D dir)
{
    Vector2D tileIndexPosition = arrayIndex + (dir);
    if (!IsValidIndex(tileIndexPosition))
        return Vector2D::None();
    if (IsTileAlly(boardTiles[tileIndexPosition], pieceColor))
    {
        return Vector2D::None();
    }
    else if (IsTileEnemy(boardTiles[tileIndexPosition], pieceColor))
    {
        return tileIndexPosition;
    }
    else if (IsTileEmpty(boardTiles[tileIndexPosition]))
    {
        return tileIndexPosition;
    }
    return tileIndexPosition;
}
bool Board::IsValidIndex(Vector2D arrayIndex)
{
    return arrayIndex.x < 8 && arrayIndex.x >= 0 && arrayIndex.y < 8 && arrayIndex.y >= 0;
}
Vector2D Board::WorldPosToBoard(Vector2D worldPos)
{
    int x = (((worldPos.x - startingPosX) / tileSize) - 1);
    int y = (((worldPos.y - startingPosY) / tileSize) - 1);
    return Vector2D(x,y);
}
Vector2D Board::BoardToWorldPos(Vector2D boardPos) 
{
    return Vector2D(startingPosX + (tileSize * (1 + boardPos.x)), startingPosY + (tileSize * (1 + boardPos.y)));
}
bool Board::CanMoveToTile(Tile* tile, PieceColor color)
{
    return tile->piece->GetColor() != color;
}
bool Board::IsTileEmpty(Tile* tile)
{
    return tile->piece->GetColor() == NONE;
}
bool Board::IsTileAlly(Tile* tile, PieceColor color)
{
    return tile->piece->GetColor() == color;
}
bool Board::IsTileEnemy(Tile* tile, PieceColor color)
{
    return tile->piece->GetColor() == -color;
}
void Board::TrySelectPiece(Vector2D boardIndex)
{
    if (boardTiles[boardIndex]->type == PieceType::None)
        return;
    if (boardTiles[boardIndex]->piece->GetColor() != currentPlayer->playerColor)
        return;
    if (currentPlayer->jaque)
    {
        pickedPieceTile = boardTiles[boardIndex];
        ResetPosibleMoves();
        PosibleMoves(pickedPieceTile->piece->GetPosiblesMoves(boardIndex, *this, currentPlayer->playerColor));
        int size = pickedPieceTile->piece->posibleMoves.size();
        if (size <= 0)
            pickedPieceTile = nullptr;
    }
    else
    {
        pickedPieceTile = boardTiles[boardIndex];
        ResetPosibleMoves();
        PosibleMoves(pickedPieceTile->piece->GetPosiblesMoves(boardIndex, *this, currentPlayer->playerColor));
        int size = pickedPieceTile->piece->posibleMoves.size();
        if (size <= 0)
            pickedPieceTile = nullptr;
    }
}


void Board::TryReleasePiece(Vector2D releaseBoardIndex)
{
    if (boardTiles[Vector2D(releaseBoardIndex)]->piece->GetColor() != currentPlayer->playerColor)
    {
        if (pickedPieceTile == nullptr)
            return;
        if (pickedPieceTile->piece->CheckMove(releaseBoardIndex))
        {
            Vector2D boardPos = WorldPosToBoard(pickedPieceTile->piece->GetPos());
            Vector2D pixelPos = pickedPieceTile->piece->GetPos();
            pickedPieceTile->piece->alreadyMoved = true;

            pickedPieceTile->piece->SetPosition(boardTiles[releaseBoardIndex]->pos);
            boardTiles[releaseBoardIndex]->piece = pickedPieceTile->piece;
            boardTiles[releaseBoardIndex]->type = pickedPieceTile->type;


            boardTiles[boardPos]->piece = GetEmptyPiece(pixelPos);
            boardTiles[boardPos]->type = None;

            pickedPieceTile = nullptr;
            ResetPosibleMoves();

            //Mandar socket a todos los player

            currentPlayer->jaque = false;
            currentPlayer->jaqueMate = false;

            currentPlayer = (currentPlayer->playerColor == WHITE) ? players[1] : players[0];

            CheckJaque(currentPlayer->playerColor);
        }
    }
}

void Board::run()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "Chess The Game Of Kings!");

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);

        sf::Drawable* drawable = &board;
        window.draw(*drawable); //Pintar els renderizables

        for (int i = 0; i < 8; i++)
        {
            for (int e = 0; e < 8; e++)
            {
                sf::Drawable* drawable = boardTiles[Vector2D(i, e)]->piece;
                if (drawable != nullptr)
                {
                    window.draw(*drawable); //Pintar els renderizables
                }
                sf::Drawable* drawable2 = boardTiles[Vector2D(i, e)]->marca;
                if (drawable != nullptr)
                {
                    window.draw(*drawable2); //Pintar els renderizables
                }
            }
        }

        window.display();

        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i clickPixelPos = { event.mouseButton.x, event.mouseButton.y };
                    Vector2D mouseBoardIndex = WorldPosToBoard(Vector2D(clickPixelPos.x, clickPixelPos.y));

                    TrySelectPiece(mouseBoardIndex);

                    if (pickedPieceTile != nullptr)
                        TryReleasePiece(mouseBoardIndex);
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                }
                break;
            case sf::Event::MouseWheelScrolled:
                //No hace falta
                break;
            default:
                break;
            }
        }
    }
}

