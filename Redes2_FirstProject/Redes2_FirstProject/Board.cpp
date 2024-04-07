#pragma once
#include "Pieces.h"
#include "Board.h"



Board::Board()
{
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
                case 3:
                    type = PieceType::Queen;
                    piece = new queen(texturesPiece, pixelPos);
                    piece->SetPiece(sf::IntRect(64, textureYCord, 64, 64), color);
                    break;
                case 4:
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
void Board::TrySelectPiece(sf::Vector2f worldPos)
{
    for (int i = 0; i < 8; i++)
    {
        for (int e = 0; e < 8; e++)
        {

            if (boardTiles[Vector2D(i, e)]->type != PieceType::None)
            {
                if (boardTiles[Vector2D(i, e)]->piece->GetColor() == PieceColor::WHITE)
                {
                    if (boardTiles[Vector2D(i, e)]->piece->CheckBounds(worldPos.x, worldPos.y))
                    {
                        pressedTile = boardTiles[Vector2D(i, e)];

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


            if (boardTiles[Vector2D(i, e)]->piece->GetColor() != PieceColor::WHITE)
            {
                if (boardTiles[Vector2D(i, e)]->piece->CheckBounds(worldPos.x, worldPos.y))
                {
                    if (pressedTile == nullptr)
                        return;
                    if (pressedTile->piece->CheckMove(Vector2D(i, e)))
                    {
                        Vector2D boardPos = pressedTile->boardPos;
                        Vector2D pixelPos = pressedTile->piece->GetPos();

                        pressedTile->piece->SetPosition(boardTiles[Vector2D(i, e)]->pos);
                        boardTiles[Vector2D(i, e)]->piece = pressedTile->piece;
                        boardTiles[Vector2D(i, e)]->type = pressedTile->type;


                        boardTiles[boardPos]->piece = GetEmptyPiece(pixelPos);
                        boardTiles[boardPos]->type = None;

                        pressedTile = nullptr;

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
                    if (pressedTile == nullptr)
                        TrySelectPiece(worldPos);
                    else
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
    this->piece = piece;
    this->type = type;
    this->boardPos = boardPos;
}
