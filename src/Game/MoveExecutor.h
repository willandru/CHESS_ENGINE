#pragma once

#include "GameState.h"
#include "Move.h"

class MoveExecutor
{
public:

    // Aplica un movimiento al estado
    static void execute(
        GameState& state,
        const Move& move
    );

    // Revertir movimiento (útil para IA)
    static void undo(
        GameState& state,
        const Move& move
    );
};