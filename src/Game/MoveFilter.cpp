#include "MoveFilter.h"
#include "MoveExecutor.h"
#include "MoveGenerator.h"
#include "ChessRules.h"

//====================================================
// FILTER LEGAL MOVES
//====================================================
void MoveFilter::filterLegalMoves(
    const GameState& state,
    std::vector<Move>& moves)
{
    std::vector<Move> legal;
    legal.reserve(moves.size());

    PlayerSide side = state.getTurn();

    for (const Move& m : moves)
    {
        GameState copy = state;

        MoveExecutor::execute(copy, m);

        if (!isKingInCheck(copy, side))
            legal.push_back(m);
    }

    moves = std::move(legal);
}

//====================================================
// CHECK
//====================================================
bool MoveFilter::isKingInCheck(
    const GameState& state,
    PlayerSide side)
{
    uint8_t kingSq = findKing(state, side);

    if (kingSq == 255)
        return false;

    PlayerSide enemy =
        (side == PlayerSide::White)
        ? PlayerSide::Black
        : PlayerSide::White;

    return isSquareAttacked(state, kingSq, enemy);
}

//====================================================
// FIND KING
//====================================================
uint8_t MoveFilter::findKing(
    const GameState& state,
    PlayerSide side)
{
    for (uint8_t sq = 0; sq < 64; ++sq)
    {
        Piece p = state.getPiece(sq);

        if (side == PlayerSide::White && p == WHITE_KING)
            return sq;

        if (side == PlayerSide::Black && p == BLACK_KING)
            return sq;
    }

    return 255;
}

//====================================================
// ATTACK DETECTION
//====================================================
bool MoveFilter::isSquareAttacked(
    const GameState& state,
    uint8_t square,
    PlayerSide attackerSide)
{
    for (uint8_t sq = 0; sq < 64; ++sq)
    {
        Piece p = state.getPiece(sq);

        if (p == EMPTY)
            continue;

        if (attackerSide == PlayerSide::White &&
            !ChessRules::isWhitePiece(p))
            continue;

        if (attackerSide == PlayerSide::Black &&
            ChessRules::isWhitePiece(p))
            continue;

        if (MoveGenerator::attacksSquare(state, sq, square))
            return true;
    }

    return false;
}

//====================================================
// CHECKMATE
//====================================================
bool MoveFilter::isCheckmate(
    const GameState& state,
    PlayerSide side)
{
    if (!isKingInCheck(state, side))
        return false;

    std::vector<Move> moves;
    MoveGenerator::generateAllMoves(state, moves);

    filterLegalMoves(state, moves);

    return moves.empty();
}

//====================================================
// STALEMATE
//====================================================
bool MoveFilter::isStalemate(
    const GameState& state,
    PlayerSide side)
{
    if (isKingInCheck(state, side))
        return false;

    std::vector<Move> moves;
    MoveGenerator::generateAllMoves(state, moves);

    filterLegalMoves(state, moves);

    return moves.empty();
}

//====================================================
// GAME STATUS (API FINAL)
//====================================================
MoveFilter::GameStateStatus MoveFilter::getGameStatus(
    const GameState& state,
    PlayerSide side)
{
    if (isCheckmate(state, side))
        return GameStateStatus::Checkmate;

    if (isStalemate(state, side))
        return GameStateStatus::Stalemate;

    if (isKingInCheck(state, side))
        return GameStateStatus::Check;

    return GameStateStatus::Normal;
}