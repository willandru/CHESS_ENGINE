#include "GameState.h"
#include "InitialPosition.h"
#include <string>


//====================================================
// INIT
//====================================================

GameState::GameState()
{
    reset();
}

//====================================================
// STATE RESET
//====================================================

void GameState::clear()
{
    for (int i = 0; i < 64; ++i)
        board[i] = EMPTY;

    turn = PlayerSide::White;

    enPassantSquare = 255;

    castleRights = 0;

    halfMoveClock = 0;
}

void GameState::reset()
{
    clear();

    //================ BLACK =================
    board[InitialPosition::BLACK_ROOK_QUEENSIDE]   = BLACK_ROOK;
    board[InitialPosition::BLACK_KNIGHT_QUEENSIDE] = BLACK_KNIGHT;
    board[InitialPosition::BLACK_BISHOP_QUEENSIDE] = BLACK_BISHOP;
    board[InitialPosition::BLACK_QUEEN]            = BLACK_QUEEN;
    board[InitialPosition::BLACK_KING]             = BLACK_KING;
    board[InitialPosition::BLACK_BISHOP_KINGSIDE]  = BLACK_BISHOP;
    board[InitialPosition::BLACK_KNIGHT_KINGSIDE]  = BLACK_KNIGHT;
    board[InitialPosition::BLACK_ROOK_KINGSIDE]    = BLACK_ROOK;

    for (uint8_t c = 0; c < 8; ++c)
        board[getSquare(1, c)] = BLACK_PAWN;

    //================ WHITE =================
    for (uint8_t c = 0; c < 8; ++c)
        board[getSquare(6, c)] = WHITE_PAWN;

    board[InitialPosition::WHITE_ROOK_QUEENSIDE]   = WHITE_ROOK;
    board[InitialPosition::WHITE_KNIGHT_QUEENSIDE] = WHITE_KNIGHT;
    board[InitialPosition::WHITE_BISHOP_QUEENSIDE] = WHITE_BISHOP;
    board[InitialPosition::WHITE_QUEEN]            = WHITE_QUEEN;
    board[InitialPosition::WHITE_KING]             = WHITE_KING;
    board[InitialPosition::WHITE_BISHOP_KINGSIDE]  = WHITE_BISHOP;
    board[InitialPosition::WHITE_KNIGHT_KINGSIDE]  = WHITE_KNIGHT;
    board[InitialPosition::WHITE_ROOK_KINGSIDE]    = WHITE_ROOK;

    turn = PlayerSide::White;

    enPassantSquare = 255;

    castleRights = ALL_CASTLING_RIGHTS;

    halfMoveClock = 0;
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
// EN PASSANT
//====================================================

uint8_t GameState::getEnPassantSquare() const
{
    return enPassantSquare;
}

void GameState::setEnPassantSquare(uint8_t square)
{
    enPassantSquare = square;
}

void GameState::clearEnPassant()
{
    enPassantSquare = 255;
}

//====================================================
// CASTLING RIGHTS
//====================================================

uint8_t GameState::getCastleRights() const
{
    return castleRights;
}

void GameState::setCastleRights(uint8_t rights)
{
    castleRights = rights;
}

bool GameState::canCastleKingside(PlayerSide side) const
{
    if (side == PlayerSide::White)
        return (castleRights & WHITE_KINGSIDE) != 0;

    return (castleRights & BLACK_KINGSIDE) != 0;
}

bool GameState::canCastleQueenside(PlayerSide side) const
{
    if (side == PlayerSide::White)
        return (castleRights & WHITE_QUEENSIDE) != 0;

    return (castleRights & BLACK_QUEENSIDE) != 0;
}

void GameState::removeKingsideCastle(PlayerSide side)
{
    if (side == PlayerSide::White)
        castleRights &= ~WHITE_KINGSIDE;
    else
        castleRights &= ~BLACK_KINGSIDE;
}

void GameState::removeQueensideCastle(PlayerSide side)
{
    if (side == PlayerSide::White)
        castleRights &= ~WHITE_QUEENSIDE;
    else
        castleRights &= ~BLACK_QUEENSIDE;
}

void GameState::removeAllCastle(PlayerSide side)
{
    if (side == PlayerSide::White)
    {
        castleRights &= ~(WHITE_KINGSIDE | WHITE_QUEENSIDE);
    }
    else
    {
        castleRights &= ~(BLACK_KINGSIDE | BLACK_QUEENSIDE);
    }
}

//====================================================
// FIFTY-MOVE RULE
//====================================================

uint16_t GameState::getHalfMoveClock() const
{
    return halfMoveClock;
}

void GameState::setHalfMoveClock(uint16_t value)
{
    halfMoveClock = value;
}

void GameState::resetHalfMoveClock()
{
    halfMoveClock = 0;
}

void GameState::incrementHalfMoveClock()
{
    ++halfMoveClock;
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


std::string GameState::squareToNotation(uint8_t square)
{
    char file = 'a' + getCol(square);
    char rank = '8' - getRow(square);

    return std::string{file, rank};
}

uint8_t GameState::notationToSquare(
    const std::string& notation)
{
    if (notation.size() != 2)
        return 255;

    uint8_t col = notation[0] - 'a';
    uint8_t row = '8' - notation[1];

    return getSquare(row, col);
}