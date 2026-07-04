#include "GameState.h"

#include "InitialPosition.h"

GameState::GameState()
{
    reset();
}

//====================================================
// STATE
//====================================================

void GameState::clear()
{
    for (int i = 0; i < 64; ++i)
        board[i] = EMPTY;

    turn = PlayerSide::White;
}

void GameState::reset()
{
    clear();

    //------------------------------------------------
    // BLACK PIECES
    //------------------------------------------------

    board[InitialPosition::BLACK_ROOK_QUEENSIDE]   = BLACK_ROOK;
    board[InitialPosition::BLACK_KNIGHT_QUEENSIDE] = BLACK_KNIGHT;
    board[InitialPosition::BLACK_BISHOP_QUEENSIDE] = BLACK_BISHOP;
    board[InitialPosition::BLACK_QUEEN]            = BLACK_QUEEN;
    board[InitialPosition::BLACK_KING]             = BLACK_KING;
    board[InitialPosition::BLACK_BISHOP_KINGSIDE]  = BLACK_BISHOP;
    board[InitialPosition::BLACK_KNIGHT_KINGSIDE]  = BLACK_KNIGHT;
    board[InitialPosition::BLACK_ROOK_KINGSIDE]    = BLACK_ROOK;

    for (uint8_t col = 0; col < 8; ++col)
    {
        board[getSquare(InitialPosition::BLACK_PAWN_ROW, col)] = BLACK_PAWN;
    }

    //------------------------------------------------
    // WHITE PIECES
    //------------------------------------------------

    for (uint8_t col = 0; col < 8; ++col)
    {
        board[getSquare(InitialPosition::WHITE_PAWN_ROW, col)] = WHITE_PAWN;
    }

    board[InitialPosition::WHITE_ROOK_QUEENSIDE]   = WHITE_ROOK;
    board[InitialPosition::WHITE_KNIGHT_QUEENSIDE] = WHITE_KNIGHT;
    board[InitialPosition::WHITE_BISHOP_QUEENSIDE] = WHITE_BISHOP;
    board[InitialPosition::WHITE_QUEEN]            = WHITE_QUEEN;
    board[InitialPosition::WHITE_KING]             = WHITE_KING;
    board[InitialPosition::WHITE_BISHOP_KINGSIDE]  = WHITE_BISHOP;
    board[InitialPosition::WHITE_KNIGHT_KINGSIDE]  = WHITE_KNIGHT;
    board[InitialPosition::WHITE_ROOK_KINGSIDE]    = WHITE_ROOK;

    turn = PlayerSide::White;
}

//====================================================
// BOARD
//====================================================

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

//====================================================
// TURN
//====================================================

PlayerSide GameState::getTurn() const
{
    return turn;
}

void GameState::setTurn(PlayerSide side)
{
    turn = side;
}

void GameState::switchTurn()
{
    turn = (turn == PlayerSide::White)
        ? PlayerSide::Black
        : PlayerSide::White;
}

//====================================================
// COORDINATES
//====================================================

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

uint8_t GameState::findKing(PlayerSide side) const
{
    for (uint8_t sq = 0; sq < 64; ++sq)
    {
        Piece p = board[sq];

        if (side == PlayerSide::White && p == WHITE_KING)
            return sq;

        if (side == PlayerSide::Black && p == BLACK_KING)
            return sq;
    }

    return 255;
}