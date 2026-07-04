#include "MoveExecutor.h"

#include "ChessTypes.h"
#include <iostream>

void MoveExecutor::execute(
    GameState& state,
    const Move& move)
{
    Piece piece = state.getPiece(move.from);

    if (piece == EMPTY)
        return;

    //=========================================
    // GUARDAR PIEZA CAPTURADA
    //=========================================
    Piece captured = state.getPiece(move.to);

    // IMPORTANTE: guardar para undo / IA
    const_cast<Move&>(move).captured = captured;

    //=========================================
    // MOVIMIENTO BASE
    //=========================================
    state.setPiece(move.to, piece);
    state.setPiece(move.from, EMPTY);

    //=========================================
    // PROMOCIÓN
    //=========================================
    if (move.isPromotion())
    {
        state.setPiece(move.to, move.promo);
    }

    //=========================================
    // EN PASSANT (placeholder)
    //=========================================
    if (move.isEnPassant())
    {
        uint8_t capSquare =
            (GameState::getRow(move.to) + (piece == WHITE_PAWN ? 1 : -1)) * 8
            + GameState::getCol(move.to);

        state.setPiece(capSquare, EMPTY);
    }

    //=========================================
    // CASTLING (placeholder)
    //=========================================
    if (move.isCastling())
    {
        // futuro: mover torre automáticamente
    }

    //=========================================
    // DEBUG
    //=========================================
    std::cout
        << "Move executed: "
        << (int)move.from
        << " -> "
        << (int)move.to
        << "\n";
}

void MoveExecutor::undo(
    GameState& state,
    const Move& move)
{
    Piece moved = state.getPiece(move.to);

    state.setPiece(move.from, moved);
    state.setPiece(move.to, move.captured);

    std::cout
        << "Undo move\n";
}