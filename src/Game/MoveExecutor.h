#pragma once

#include "GameState.h"
#include "Move.h"

class MoveExecutor
{
public:
    static bool execute(GameState& state, const Move& move);
    static void undo(GameState& state, const Move& move);
};