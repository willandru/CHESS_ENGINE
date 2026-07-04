#pragma once

#include <cstdint>
#include <vector>

#include "GameState.h"
#include "Move.h"

class PawnMoves
{
public:

    static void generate(
        const GameState& state,
        uint8_t square,
        std::vector<Move>& moves
    );

private:

    static void addMove(
        const GameState& state,
        uint8_t from,
        uint8_t to,
        std::vector<Move>& moves
    );

    static bool isEnemy(
        Piece a,
        Piece b
    );
};