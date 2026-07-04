#include "MoveExecutor.h"
#include "ChessRules.h"
#include <iostream>

//====================================================
// EXECUTE MOVE
//====================================================

bool MoveExecutor::execute(GameState& state, const Move& move)
{
    Piece piece = state.getPiece(move.from);

    if (piece == EMPTY)
        return false;

    Piece target = state.getPiece(move.to);

    //================================================
    // APPLY MOVE (BASE)
    //================================================
    state.setPiece(move.to, piece);
    state.setPiece(move.from, EMPTY);

    //================================================
    // STORE CAPTURE
    //================================================
    const_cast<Move&>(move).captured = target;

    //================================================
    // PROMOTION
    //================================================
    if (move.isPromotion())
    {
        state.setPiece(move.to, move.promo);
    }

    //================================================
    // EN PASSANT
    //================================================
    if (move.isEnPassant())
    {
        int dir = ChessRules::pawnDirection(piece);

        uint8_t capSquare =
            GameState::getSquare(
                GameState::getRow(move.to) - dir,
                GameState::getCol(move.to)
            );

        state.setPiece(capSquare, EMPTY);
    }

    //================================================
    // CASTLING (placeholder)
    //================================================
    if (move.isCastling())
    {
        // TODO: mover torre cuando lo implementes
    }

    //================================================
    // SWITCH TURN (CRITICAL)
    //================================================
    state.switchTurn();

    return true;
}

//====================================================
// UNDO MOVE
//====================================================

void MoveExecutor::undo(GameState& state, const Move& move)
{
    Piece moved = state.getPiece(move.to);

    state.setPiece(move.from, moved);
    state.setPiece(move.to, move.captured);

    // revert turn
    state.switchTurn();
}