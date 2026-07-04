#include "GameState.h"

#include "ChessBoardRenderer.h"

#include <iostream>

GameState::GameState()
{
    reset();
}

void GameState::reset()
{
    for (int i = 0; i < 64; ++i)
    {
        board[i] = EMPTY;
    }

    //----------------------------------------
    // BLACK
    //----------------------------------------

    board[0] = BLACK_ROOK;
    board[1] = BLACK_KNIGHT;
    board[2] = BLACK_BISHOP;
    board[3] = BLACK_QUEEN;
    board[4] = BLACK_KING;
    board[5] = BLACK_BISHOP;
    board[6] = BLACK_KNIGHT;
    board[7] = BLACK_ROOK;

    for (int i = 8; i < 16; ++i)
    {
        board[i] = BLACK_PAWN;
    }

    //----------------------------------------
    // WHITE
    //----------------------------------------

    board[56] = WHITE_ROOK;
    board[57] = WHITE_KNIGHT;
    board[58] = WHITE_BISHOP;
    board[59] = WHITE_QUEEN;
    board[60] = WHITE_KING;
    board[61] = WHITE_BISHOP;
    board[62] = WHITE_KNIGHT;
    board[63] = WHITE_ROOK;

    for (int i = 48; i < 56; ++i)
    {
        board[i] = WHITE_PAWN;
    }

    selected = false;
    selectedSquare = 0;
}

const Piece* GameState::getBoard() const
{
    return board;
}

Piece GameState::getPiece(uint8_t square) const
{
    return board[square];
}

void GameState::setPiece(
    uint8_t square,
    Piece piece)
{
    board[square] = piece;
}

bool GameState::hasSelection() const
{
    return selected;
}

uint8_t GameState::getSelectedSquare() const
{
    return selectedSquare;
}

uint8_t GameState::getSquare(
    uint8_t row,
    uint8_t col)
{
    return row * 8 + col;
}

uint8_t GameState::getRow(
    uint8_t square)
{
    return square / 8;
}

uint8_t GameState::getCol(
    uint8_t square)
{
    return square % 8;
}

bool GameState::mouseToSquare(
    float mouseX,
    float mouseY,
    uint8_t& row,
    uint8_t& col,
    uint8_t& square) const
{
    const BoardLayout layout =
        ChessBoardRenderer::getLayout();

    if (mouseX < layout.x)
        return false;

    if (mouseY < layout.y)
        return false;

    if (mouseX >= layout.x + layout.boardSize)
        return false;

    if (mouseY >= layout.y + layout.boardSize)
        return false;

    col = static_cast<uint8_t>(
        (mouseX - layout.x) / layout.squareSize);

    row = static_cast<uint8_t>(
        (mouseY - layout.y) / layout.squareSize);

    square = getSquare(row, col);

    return true;
}

bool GameState::hasPiece(
    uint8_t square) const
{
    return board[square] != EMPTY;
}

void GameState::selectPiece(
    uint8_t square)
{
    selected = true;
    selectedSquare = square;

    std::cout
        << "Selected piece\n"
        << "square : " << (int)square
        << "\n";
}

void GameState::moveSelectedPiece(
    uint8_t destination)
{
    board[destination] =
        board[selectedSquare];

    board[selectedSquare] =
        EMPTY;

    std::cout
        << "Move "
        << (int)selectedSquare
        << " -> "
        << (int)destination
        << "\n";

    selected = false;
}

void GameState::onMouseClick(
    float mouseX,
    float mouseY)
{
    uint8_t row;
    uint8_t col;
    uint8_t square;

    if (!mouseToSquare(
            mouseX,
            mouseY,
            row,
            col,
            square))
    {
        std::cout
            << "Click outside board\n";

        selected = false;

        return;
    }

    std::cout
        << "row    : " << (int)row << '\n'
        << "col    : " << (int)col << '\n'
        << "square : " << (int)square << '\n';

    if (!selected)
    {
        if (hasPiece(square))
        {
            selectPiece(square);
        }

        return;
    }

    moveSelectedPiece(square);
}