#pragma once
#include "Pieces.h"
#include "Board.h"



Board::Board()
{
    pressedPiece = nullptr;
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
    float posX = 5, posY = 5;
    float size = 84;


    for (int i = 0; i < 8; i++)
    {
        for (int e = 0; e < 8; e++)
        {
            pieces.emplace(Vector2D(i,e),nullptr);
            boardPos.emplace(Vector2D(i, e), Vector2D(posX + (size * (1 + e)), posY + (size * (1 + i))));


        }
    }
    boardPieces[Vector2D(0, 0)] = TowerWhite;
    boardPieces[Vector2D(0, 1)] = KnightWhite;
    boardPieces[Vector2D(0, 2)] = BishopWhite;
    boardPieces[Vector2D(0, 3)] = QueenWhite;
    boardPieces[Vector2D(0, 4)] = KingWhite;
    boardPieces[Vector2D(0, 5)] = BishopWhite;
    boardPieces[Vector2D(0, 6)] = KnightWhite;
    boardPieces[Vector2D(0, 7)] = TowerWhite;
    for (int i = 0; i <= 8; ++i) {
        boardPieces[Vector2D(1, i)] = PawnWhite;
        boardPieces[Vector2D(6, i)] = PawnBlack;
    }
    boardPieces[Vector2D(7, 0)] = TowerBlack;
    boardPieces[Vector2D(7, 1)] = KnightBlack;
    boardPieces[Vector2D(7, 2)] = BishopBlack;
    boardPieces[Vector2D(7, 3)] = QueenBlack;
    boardPieces[Vector2D(7, 4)] = KingBlack;
    boardPieces[Vector2D(7, 5)] = BishopBlack;
    boardPieces[Vector2D(7, 6)] = KnightBlack;
    boardPieces[Vector2D(7, 7)] = TowerBlack;

}

void Board::UpdateBoard()
{
    for (int i = 0; i < 8; i++)
    {
        for (int e = 0; e < 8; e++)
        {
            PieceType piece;

            piece = boardPieces[Vector2D(i, e)];

            pieces[Vector2D(i, e)] = nullptr;
            switch(piece)
            {
            case PawnWhite:
                pieces[Vector2D(i, e)] = new pawn(texturesPiece, boardPos[Vector2D(i, e)]);
                pieces[Vector2D(i, e)]->SetPiece(sf::IntRect(320, 64, 64, 64), PieceColor::WHITE);
                break;
            case KnightWhite:
                pieces[Vector2D(i, e)] = new knight(texturesPiece, boardPos[Vector2D(i, e)]);
                pieces[Vector2D(i, e)]->SetPiece(sf::IntRect(192, 64, 64, 64), PieceColor::WHITE);
                break;
            case BishopWhite:
                pieces[Vector2D(i, e)] = new bishop(texturesPiece, boardPos[Vector2D(i, e)]);
                pieces[Vector2D(i, e)]->SetPiece(sf::IntRect(256, 64, 64, 64), PieceColor::WHITE);
                break;
            case TowerWhite:

                pieces[Vector2D(i, e)] = new tower(texturesPiece, boardPos[Vector2D(i, e)]);
                pieces[Vector2D(i, e)]->SetPiece(sf::IntRect(128, 64, 64, 64), PieceColor::WHITE);
                break;
            case QueenWhite:
                pieces[Vector2D(i, e)] = new queen(texturesPiece, boardPos[Vector2D(i, e)]);
                pieces[Vector2D(i, e)]->SetPiece(sf::IntRect(64, 64, 64, 64), PieceColor::WHITE);
                break;
            case KingWhite:
                pieces[Vector2D(i, e)] = new king(texturesPiece, boardPos[Vector2D(i, e)]);
                pieces[Vector2D(i, e)]->SetPiece(sf::IntRect(0, 64, 64, 64), PieceColor::WHITE);
                break;
            case PawnBlack:
                pieces[Vector2D(i, e)] = new pawn(texturesPiece, boardPos[Vector2D(i, e)]);
                pieces[Vector2D(i, e)]->SetPiece(sf::IntRect(320, 0, 64, 64), PieceColor::BLACK);
                break;
            case KnightBlack:
                pieces[Vector2D(i, e)] = new knight(texturesPiece, boardPos[Vector2D(i, e)]);
                pieces[Vector2D(i, e)]->SetPiece(sf::IntRect(192, 0, 64, 64), PieceColor::BLACK);
                break;
            case BishopBlack:
                pieces[Vector2D(i, e)] = new bishop(texturesPiece, boardPos[Vector2D(i, e)]);
                pieces[Vector2D(i, e)]->SetPiece(sf::IntRect(256, 0, 64, 64), PieceColor::BLACK);
                break;
            case TowerBlack:
                pieces[Vector2D(i, e)] = new tower(texturesPiece, boardPos[Vector2D(i, e)]);
                pieces[Vector2D(i, e)]->SetPiece(sf::IntRect(128, 0, 64, 64), PieceColor::BLACK);
                break;
            case QueenBlack:
                pieces[Vector2D(i, e)] = new queen(texturesPiece, boardPos[Vector2D(i, e)]);
                pieces[Vector2D(i, e)]->SetPiece(sf::IntRect(64, 0, 64, 64), PieceColor::BLACK);
                break;
            case KingBlack:
                pieces[Vector2D(i, e)] = new king(texturesPiece, boardPos[Vector2D(i, e)]);
                pieces[Vector2D(i, e)]->SetPiece(sf::IntRect(0, 0, 64, 64), PieceColor::BLACK);
                break;
            case None:
                pieces[Vector2D(i, e)] = new Piece(texturesPiece, boardPos[Vector2D(i, e)]);
                pieces[Vector2D(i, e)]->SetPiece(sf::IntRect(50, 50, 64, 64), PieceColor::NONE);
                pieces[Vector2D(i, e)]->setColor(sf::Color(0, 0, 0, 0));
                break;
            default:
                break;
            }
            pieces[Vector2D(i, e)]->setScale(1.2, 1.2);
        }
    }

}

void Board::run()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "Chess The Game Of Kings!");
    UpdateBoard();

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);

        sf::Drawable* drawable = &board;
        window.draw(*drawable); //Pintar els renderizables

        for (int i = 0; i < 8; i++)
        {
            for (int e = 0; e < 8; e++)
            {
                sf::Drawable* drawable = pieces[Vector2D(i, e)];
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
            if (pressedPiece != nullptr)
            {
                pressedPiece->SetPosition(Vector2D(worldPos.x - 32, worldPos.y - 32));
            }

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:

                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    for (int i = 0; i < 8; i++)
                    {
                        for (int e = 0; e < 8; e++)
                        {
                            if (pieces[Vector2D(i, e)]->CheckBounds(worldPos.x, worldPos.y) && pressedPiece == nullptr)
                            {
                                pressedPiece = pieces[Vector2D(i, e)];
                                
                            }

                        }
                    }
          
                }

                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    if (pressedPiece != nullptr)
                    {
                        pressedPiece = nullptr;
                    }

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
