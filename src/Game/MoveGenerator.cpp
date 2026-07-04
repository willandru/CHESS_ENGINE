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
        // FUTURE PIECES
        //=========================
        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            // KnightMoves::generate(state, square, moves);
            break;

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            // BishopMoves::generate(state, square, moves);
            break;

        case WHITE_ROOK:
        case BLACK_ROOK:
            // RookMoves::generate(state, square, moves);
            break;

        case WHITE_QUEEN:
        case BLACK_QUEEN:
            // QueenMoves::generate(state, square, moves);
            break;

        case WHITE_KING:
        case BLACK_KING:
            // KingMoves::generate(state, square, moves);
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

//==================================================
// HELPERS (FUTURO TURN SYSTEM)
//==================================================

bool MoveGenerator::isWhitePiece(Piece p)
{
    return p >= WHITE_PAWN && p <= WHITE_KING;
}

bool MoveGenerator::isBlackPiece(Piece p)
{
    return p >= BLACK_PAWN && p <= BLACK_KING;
}