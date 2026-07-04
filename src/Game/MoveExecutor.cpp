#include "MoveExecutor.h"

#include "ChessTypes.h"

void MoveExecutor::execute(
    GameState& state,
    const Move& move)
{
    Piece piece = state.getPiece(move.from);

    if (piece == EMPTY)
        return;

    //=========================================
    // CAPTURA
    //=========================================
    // (solo reemplazamos destino)
    //=========================================

    state.setPiece(move.to, piece);
    state.setPiece(move.from, EMPTY);

    //=========================================
    // PROMOCIÓN (simple placeholder)
    //=========================================
    if (move.isPromotion())
    {
        state.setPiece(move.to, move.promo);
    }

    //=========================================
    // EN PASSANT (placeholder lógico)
    //=========================================
    if (move.isEnPassant())
    {
        // eliminar pieza capturada en casilla intermedia
        // (pendiente extender cuando implementes regla completa)
    }

    //=========================================
    // CASTLING (placeholder)
    //=========================================
    if (move.isCastling())
    {
        // mover torre correspondiente
        // (se implementa cuando agregues king moves)
    }

    //=========================================
    // DEBUG OUTPUT
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
    // restaurar pieza original
    Piece moved = state.getPiece(move.to);

    state.setPiece(move.from, moved);

    // restaurar casilla destino (simplificado)
    state.setPiece(move.to, move.captured);

    std::cout
        << "Undo move\n";
}