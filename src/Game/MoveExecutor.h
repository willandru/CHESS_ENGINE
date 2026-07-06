#pragma once

#include "GameState.h"
#include "Move.h"

class MoveExecutor
{
public:

    struct Undo
    {
        Piece captured = EMPTY;

        uint8_t previousEnPassant = 255;
        uint8_t previousCastleRights = 0;

        PlayerSide previousTurn = PlayerSide::White;

        // Regla de los 50 movimientos
        uint16_t previousHalfMoveClock = 0;
    };

    static Undo execute(
        GameState& state,
        const Move& move);

    static void undo(
        GameState& state,
        const Move& move,
        const Undo& undo);
};