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
        board[i] = EMPTY;

    // ---------------- BLACK ----------------
    board[0] = BLACK_ROOK;
    board[1] = BLACK_KNIGHT;
    board[2] = BLACK_BISHOP;
    board[3] = BLACK_QUEEN;
    board[4] = BLACK_KING;
    board[5] = BLACK_BISHOP;
    board[6] = BLACK_KNIGHT;
    board[7] = BLACK_ROOK;

    for (int i = 8; i < 16; ++i)
        board[i] = BLACK_PAWN;

    // ---------------- WHITE ----------------
    board[56] = WHITE_ROOK;
    board[57] = WHITE_KNIGHT;
    board[58] = WHITE_BISHOP;
    board[59] = WHITE_QUEEN;
    board[60] = WHITE_KING;
    board[61] = WHITE_BISHOP;
    board[62] = WHITE_KNIGHT;
    board[63] = WHITE_ROOK;

    for (int i = 48; i < 56; ++i)
        board[i] = WHITE_PAWN;

    selected = false;
    selectedSquare = 0;
}

//==================================================
// BOARD
//==================================================

Piece GameState::getPiece(uint8_t square) const
{
    return board[square];
}

void GameState::setPiece(uint8_t square, Piece piece)
{
    board[square] = piece;
}

const Piece* GameState::getBoard() const
{
    return board;
}

//==================================================
// SELECTION
//==================================================

bool GameState::hasSelection() const
{
    return selected;
}

uint8_t GameState::getSelectedSquare() const
{
    return selectedSquare;
}

void GameState::clearSelection()
{
    selected = false;
}

//==================================================
// COORDINATES
//==================================================

uint8_t GameState::getSquare(uint8_t row, uint8_t col)
{
    return row * 8 + col;
}

uint8_t GameState::getRow(uint8_t square)
{
    return square / 8;
}

uint8_t GameState::getCol(uint8_t square)
{
    return square % 8;
}

//==================================================
// INPUT MAPPING
//==================================================

bool GameState::mouseToSquare(
    float mouseX,
    float mouseY,
    uint8_t& row,
    uint8_t& col,
    uint8_t& square) const
{
    const BoardLayout layout = ChessBoardRenderer::getLayout();

    if (mouseX < layout.x ||
        mouseY < layout.y ||
        mouseX >= layout.x + layout.boardSize ||
        mouseY >= layout.y + layout.boardSize)
        return false;

    col = (mouseX - layout.x) / layout.squareSize;
    row = (mouseY - layout.y) / layout.squareSize;

    square = getSquare(row, col);
    return true;
}

bool GameState::hasPiece(uint8_t square) const
{
    return board[square] != EMPTY;
}

//==================================================
// SELECTION LOGIC
//==================================================

void GameState::selectSquare(uint8_t square)
{
    selected = true;
    selectedSquare = square;

    std::cout << "Selected: " << (int)square << "\n";
}

void GameState::movePiece(uint8_t destination)
{
    board[destination] = board[selectedSquare];
    board[selectedSquare] = EMPTY;

    std::cout
        << "Move "
        << (int)selectedSquare
        << " -> "
        << (int)destination
        << "\n";

    selected = false;
}

//==================================================
// MAIN INPUT ENTRY
//==================================================

void GameState::onMouseClick(float mouseX, float mouseY)
{
    uint8_t row, col, square;

    if (!mouseToSquare(mouseX, mouseY, row, col, square))
    {
        std::cout << "Click outside board\n";
        clearSelection();
        return;
    }

    std::cout
        << "row=" << (int)row
        << " col=" << (int)col
        << " sq=" << (int)square << "\n";

    if (!selected)
    {
        if (hasPiece(square))
            selectSquare(square);

        return;
    }

    movePiece(square);
}