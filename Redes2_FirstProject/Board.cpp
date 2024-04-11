#pragma once
#include "Pieces.h"
#include "Board.h"



Board::Board()
{
    players.push_back(new Player(WHITE));
    players.push_back(new Player(BLACK));
    currentPlayer = players[0];
    pressedTile = nullptr;
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
    float posX = 9, posY = 9;
    float size = 84;


    for (int i = 0; i < 8; i++)
    {
        for (int e = 0; e < 8; e++)
        {
            PieceType type;
            Piece* piece = new Piece();
            Vector2D pixelPos = Vector2D(posX + (size * (1 + e)), posY + (size * (1 + i)));

            PieceColor color = i <= 1 ? PieceColor::WHITE : PieceColor::BLACK;
            int textureYCord = i <= 1 ? 64 : 0;

            if (i == 0 || i == 7)     
                switch (e)
                {
                case 0:
                case 7:

                    type = PieceType::Tower;
                    piece = new tower(texturesPiece, pixelPos);
                    piece->SetPiece(sf::IntRect(128, textureYCord, 64, 64), color);
                    break;
                case 1:
                case 6:

                    type = PieceType::Knight;
                    piece = new knight(texturesPiece, pixelPos);
                    piece->SetPiece(sf::IntRect(192, textureYCord, 64, 64), color);
                    break;
                case 2:
                case 5:

                    type = PieceType::Bishop;
                    piece = new bishop(texturesPiece, pixelPos);
                    piece->SetPiece(sf::IntRect(256, textureYCord, 64, 64), color);
                    break;
                case 4:
                    type = PieceType::Queen;
                    piece = new queen(texturesPiece, pixelPos);
                    piece->SetPiece(sf::IntRect(64, textureYCord, 64, 64), color);
                    break;
                case 3:
                    type = PieceType::King;
                    piece = new king(texturesPiece, pixelPos);
                    piece->SetPiece(sf::IntRect(0, textureYCord, 64, 64), color);
                    break;

                default:
                    break;
                }
            else if (i == 1 || i == 6)
            {
                type = PieceType::Pawn;
                piece = new pawn(texturesPiece, pixelPos);
                piece->SetPiece(sf::IntRect(320, textureYCord, 64, 64), color);
            }
            else
            {
                type = PieceType::None;
                piece = GetEmptyPiece(pixelPos);
            }

         
            boardTiles.emplace(Vector2D(i,e), new Casilla(pixelPos,
                piece,
                type,
                Vector2D(i, e)));

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
    for (int i = 0; i < 8; i++)
    {
        for (int e = 0; e < 8; e++)
        {
            boardTiles[Vector2D(i, e)]->marca->setFillColor(sf::Color(0, 255, 0, 0));

        }
    }
}
std::vector<Vector2D> Board::GetEnemyPosibleMovements(PieceColor current)
{
    std::vector<Vector2D> list;
    for (int i = 0; i < 8; i++)
    {
        for (int e = 0; e < 8; e++)
        {
            if (boardTiles[Vector2D(i, e)]->piece->GetColor() == current)
            {
                if (boardTiles[Vector2D(i, e)]->type == King)
                {
                    std::vector<Vector2D> list2;
                    list2 = dynamic_cast<king*>(boardTiles[Vector2D(i, e)]->piece)->GetPosiblesMovesFake(Vector2D(i, e), *this,current);
                    list.insert(list.end(), list2.begin(), list2.end());
                }
                else if (boardTiles[Vector2D(i, e)]->type == Pawn)
                {
                    std::vector<Vector2D> list2;
                    list2 = dynamic_cast<pawn*>(boardTiles[Vector2D(i, e)]->piece)->GetPosiblesMovesFake(Vector2D(i, e), *this,current);
                    list.insert(list.end(), list2.begin(), list2.end());
                }
                else
                {
                    std::vector<Vector2D> list2;
                    list2 = boardTiles[Vector2D(i, e)]->piece->GetPosiblesMoves(Vector2D(i, e), *this,current);
                    list.insert(list.end(), list2.begin(), list2.end());
                }


            }

        }
    }


    return list;
}

void Board::CheckJaque(PieceColor current)
{
    std::vector<Vector2D> list = GetEnemyPosibleMovements(current);
    Vector2D kingPos;
    for (int i = 0; i < 8; i++)
    {
        for (int e = 0; e < 8; e++)
        {
            if (boardTiles[Vector2D(i, e)]->type == King && boardTiles[Vector2D(i, e)]->piece->GetColor() == currentPlayer->playerColor)
            {
                kingPos = Vector2D(i, e);

            }
        }
    }
    if (std::find(list.begin(), list.end(), kingPos) != list.end()) 
    {
        if(!currentPlayer->jaque)
            currentPlayer->jaque = true;
        else
            currentPlayer->jaqueMate = true;


        for (int i = 0; i < 8; i++)
        {
            for (int e = 0; e < 8; e++)
            {
                if (boardTiles[Vector2D(i, e)]->type == King && boardTiles[Vector2D(i, e)]->piece->GetColor() == currentPlayer->playerColor)
                {
                    kingPos = Vector2D(i, e);

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

void Board::TrySelectPiece(sf::Vector2f worldPos)
{
    for (int i = 0; i < 8; i++)
    {
        for (int e = 0; e < 8; e++)
        {

            if (boardTiles[Vector2D(i, e)]->type != PieceType::None)
            {
                if (boardTiles[Vector2D(i, e)]->piece->GetColor() == currentPlayer->playerColor)
                {
                    if (boardTiles[Vector2D(i, e)]->piece->CheckBounds(worldPos.x, worldPos.y))
                    {

                        if (currentPlayer->jaque)
                        {

                                pressedTile = boardTiles[Vector2D(i, e)];
                                ResetPosibleMoves();

                                PosibleMoves(pressedTile->piece->GetPosiblesMoves(Vector2D(i, e), *this, currentPlayer->playerColor));
                            
                        }
                        else
                        {
                            pressedTile = boardTiles[Vector2D(i, e)];
                            ResetPosibleMoves();

                            PosibleMoves(pressedTile->piece->GetPosiblesMoves(Vector2D(i, e),*this, currentPlayer->playerColor));
                        }
  
                    }
                }

            }


        }
    }
}


void Board::TryReleasePiece(sf::Vector2f worldPos)
{

    for (int i = 0; i < 8; i++)
    {
        for (int e = 0; e < 8; e++)
        {


            if (boardTiles[Vector2D(i, e)]->piece->GetColor() != currentPlayer->playerColor)
            {
                if (boardTiles[Vector2D(i, e)]->piece->CheckBounds(worldPos.x, worldPos.y))
                {
                    if (pressedTile == nullptr)
                        return;
                    if (pressedTile->piece->CheckMove(Vector2D(i, e)))
                    {
                        Vector2D boardPos = pressedTile->boardPos;
                        Vector2D pixelPos = pressedTile->piece->GetPos();
                        pressedTile->piece->alreadyMoved = true;

                        pressedTile->piece->SetPosition(boardTiles[Vector2D(i, e)]->pos);
                        boardTiles[Vector2D(i, e)]->piece = pressedTile->piece;
                        boardTiles[Vector2D(i, e)]->type = pressedTile->type;


                        boardTiles[boardPos]->piece = GetEmptyPiece(pixelPos);
                        boardTiles[boardPos]->type = None;

                        pressedTile = nullptr;
                        ResetPosibleMoves();

                        //Mandar socket a todos los player




                        CheckJaque((PieceColor) (-(int)currentPlayer->playerColor));

                        currentPlayer->jaque = false;
                        currentPlayer->jaqueMate = false;

                        currentPlayer = (currentPlayer->playerColor == WHITE) ? players[1] : players[0];

                        CheckJaque((PieceColor)(-(int)currentPlayer->playerColor));

                    }


                }
            }

            


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
            sf::Vector2i clickPixelPos = { event.mouseButton.x, event.mouseButton.y };
            sf::Vector2f worldPos = window.mapPixelToCoords(clickPixelPos);


            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    TrySelectPiece(worldPos);

                    if (pressedTile != nullptr)
                        TryReleasePiece(worldPos);


                  


          
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

Casilla::Casilla(Vector2D pos, Piece* piece, PieceType type, Vector2D boardPos)
{
    this->pos = pos;

    marca = new sf::RectangleShape(sf::Vector2f(64, 64));
    marca->setFillColor(sf::Color(0, 255, 0, 0)); 
    marca->setPosition(pos.x,pos.y);

    this->piece = piece;
    this->type = type;
    this->boardPos = boardPos;
}
