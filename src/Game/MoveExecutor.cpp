#include "MoveExecutor.h"

#include "ChessRules.h"

#include <cstdlib>

//====================================================
// EXECUTE MOVE
//====================================================

MoveExecutor::Undo MoveExecutor::execute(
    GameState& state,
    const Move& move)
{
    Undo undo;

    undo.captured = state.getPiece(move.to);
    undo.previousEnPassant = state.getEnPassantSquare();
    undo.previousTurn = state.getTurn();

    Piece piece = state.getPiece(move.from);

    if (piece == EMPTY)
        return undo;

    //================================================
    // RESET EN PASSANT
    //================================================

    state.clearEnPassant();

    //================================================
    // DOUBLE PAWN PUSH
    //================================================

    if (piece == WHITE_PAWN ||
        piece == BLACK_PAWN)
    {
        int fr = GameState::getRow(move.from);
        int tr = GameState::getRow(move.to);

        if (std::abs(tr - fr) == 2)
        {
            uint8_t ep =
                GameState::getSquare(
                    (fr + tr) / 2,
                    GameState::getCol(move.from));

            state.setEnPassantSquare(ep);
        }
    }

    //================================================
    // NORMAL MOVE
    //================================================

    state.setPiece(move.to, piece);
    state.setPiece(move.from, EMPTY);

    //================================================
    // PROMOTION
    //================================================

    if (move.isPromotion())
    {
        state.setPiece(
            move.to,
            move.promo);
    }

    //================================================
    // EN PASSANT
    //================================================

    if (move.isEnPassant())
    {
        int dir =
            ChessRules::pawnDirection(piece);

        uint8_t capturedSquare =
            GameState::getSquare(
                GameState::getRow(move.to) - dir,
                GameState::getCol(move.to));

        undo.captured =
            state.getPiece(capturedSquare);

        state.setPiece(
            capturedSquare,
            EMPTY);
    }

    //================================================
    // CASTLING
    //================================================

    if (move.isCastling())
    {
        // TODO
    }

    //================================================
    // NEXT TURN
    //================================================

    state.switchTurn();

    return undo;
}

//====================================================
// UNDO MOVE
//====================================================

void MoveExecutor::undo(
    GameState& state,
    const Move& move,
    const Undo& undo)
{
    state.setTurn(undo.previousTurn);

    state.setEnPassantSquare(
        undo.previousEnPassant);

    Piece moved =
        state.getPiece(move.to);

    //================================================
    // PROMOTION
    //================================================

    if (move.isPromotion())
    {
        moved = ChessRules::isWhitePiece(moved)
            ? WHITE_PAWN
            : BLACK_PAWN;
    }

    state.setPiece(
        move.from,
        moved);

    state.setPiece(
        move.to,
        undo.captured);

    //================================================
    // EN PASSANT
    //================================================

    if (move.isEnPassant())
    {
        state.setPiece(
            move.to,
            EMPTY);

        int dir =
            ChessRules::pawnDirection(moved);

        uint8_t capturedSquare =
            GameState::getSquare(
                GameState::getRow(move.to) - dir,
                GameState::getCol(move.to));

        state.setPiece(
            capturedSquare,
            undo.captured);
    }

    //================================================
    // CASTLING
    //================================================

    if (move.isCastling())
    {
        // TODO
    }
}