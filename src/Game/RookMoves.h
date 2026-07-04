#pragma once

#include <array>
#include <cstdint>

//=====================================================
// Rook geometric directions
//
// Relative directions on a 64-square board.
//
// MoveGenerator follows each direction until
// ChessRules indicates that movement must stop.
//
// These are ONLY geometric directions.
// Legality is determined by MoveGenerator using
// ChessRules and GameState.
//=====================================================

class RookMoves
{
public:

    static constexpr std::array<int8_t, 4> directions =
    {{
        -8,
         8,
        -1,
         1
    }};
};