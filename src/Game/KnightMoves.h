#pragma once

#include <array>
#include <cstdint>

//=====================================================
// Knight geometric moves
//
// Relative offsets on a 64-square board.
//
// These are ONLY geometric possibilities.
// Legality is determined by MoveGenerator using
// ChessRules and GameState.
//=====================================================

class KnightMoves
{
public:

    static constexpr std::array<int8_t, 8> moves =
    {{
        -17,
        -15,
        -10,
         -6,

          6,
         10,
         15,
         17
    }};
};