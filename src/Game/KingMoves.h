#pragma once

#include <array>
#include <cstdint>

//=====================================================
// King geometric moves
//
// Relative offsets on a 64-square board.
//
// These are ONLY geometric possibilities.
// Legality is determined by MoveGenerator using
// ChessRules and GameState.
//=====================================================

class KingMoves
{
public:

    static constexpr std::array<int8_t, 8> moves =
    {{
        -9,
        -8,
        -7,

        -1,
         1,

         7,
         8,
         9
    }};
};