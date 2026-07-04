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
    // RESET EN PASSANT BY DEFAULT
    //================================================
    state.setEnPassantSquare(255);

    //================================================
    // DETECT DOUBLE PAWN PUSH (IMPORTANT)
    //================================================
    if (piece == WHITE_PAWN || piece == BLACK_PAWN)
    {
        int fr = GameState::getRow(move.from);
        int tr = GameState::getRow(move.to);

        if (abs(tr - fr) == 2)
        {
            // square intermedio
            uint8_t epSquare = GameState::getSquare(
                (fr + tr) / 2,
                GameState::getCol(move.from)
            );

            state.setEnPassantSquare(epSquare);
        }
    }

    //================================================
    // APPLY MOVE
    //================================================
    state.setPiece(move.to, piece);
    state.setPiece(move.from, EMPTY);

    const_cast<Move&>(move).captured = target;

    //================================================
    // PROMOTION
    //================================================
    if (move.isPromotion())
    {
        state.setPiece(move.to, move.promo);
    }

    //================================================
    // EN PASSANT CAPTURE
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
    // CASTLING (unchanged)
    //================================================
    if (move.isCastling())
    {
        // TODO
    }

    //================================================
    // SWITCH TURN
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