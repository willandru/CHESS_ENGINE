#include "MoveGenerator.h"

#include "PawnMoves.h"
#include "ChessTypes.h"

void MoveGenerator::generatePieceMoves(
    const GameState& state,
    uint8_t square,
    std::vector<Move>& moves)
{
    Piece p = state.getPiece(square);

    if (p == EMPTY)
        return;

    switch (p)
    {
        //=========================
        // PAWNS
        //=========================
        case WHITE_PAWN:
        case BLACK_PAWN:
        {
            PawnMoves::generate(state, square, moves);
            break;
        }

        //=========================
        // FUTURO
        //=========================
        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            // KnightMoves::generate(...)
            break;

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            // BishopMoves::generate(...)
            break;

        case WHITE_ROOK:
        case BLACK_ROOK:
            // RookMoves::generate(...)
            break;

        case WHITE_QUEEN:
        case BLACK_QUEEN:
            // QueenMoves::generate(...)
            break;

        case WHITE_KING:
        case BLACK_KING:
            // KingMoves::generate(...)
            break;

        default:
            break;
    }
}

void MoveGenerator::generateAllMoves(
    const GameState& state,
    std::vector<Move>& moves)
{
    moves.clear();

    for (uint8_t square = 0; square < 64; ++square)
    {
        Piece p = state.getPiece(square);

        if (p == EMPTY)
            continue;

        generatePieceMoves(state, square, moves);
    }
}