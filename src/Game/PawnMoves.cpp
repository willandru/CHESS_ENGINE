#include "PawnMoves.h"

void PawnMoves::generate(
    const GameState& state,
    uint8_t square,
    std::vector<Move>& moves)
{
    Piece piece = state.getPiece(square);

    if (piece == EMPTY)
        return;

    uint8_t row = GameState::getRow(square);
    uint8_t col = GameState::getCol(square);

    int direction = 0;

    // determinar dirección
    if (piece == WHITE_PAWN)
        direction = -1;
    else if (piece == BLACK_PAWN)
        direction = 1;
    else
        return;

    int newRow = row + direction;

    if (newRow < 0 || newRow > 7)
        return;

    uint8_t forwardSquare =
        GameState::getSquare((uint8_t)newRow, col);

    Piece target = state.getPiece(forwardSquare);

    // SOLO movimiento hacia adelante si está libre
    if (target == EMPTY)
    {
        addMove(state, square, forwardSquare, moves);
    }
}

void PawnMoves::addMove(
    const GameState& state,
    uint8_t from,
    uint8_t to,
    std::vector<Move>& moves)
{
    (void)state;

    Move m;
    m.from = from;
    m.to = to;

    moves.push_back(m);
}

bool PawnMoves::isEnemy(Piece a, Piece b)
{
    if (b == EMPTY)
        return false;

    bool aWhite = (a >= WHITE_PAWN && a <= WHITE_KING);
    bool bWhite = (b >= WHITE_PAWN && b <= WHITE_KING);

    return aWhite != bWhite;
}