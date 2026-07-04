#pragma once

#include <cstdint>
#include <vector>

#include "GameState.h"
#include "Move.h"

class MoveGenerator
{
public:

    // Genera TODOS los movimientos de una pieza en una casilla
    static void generatePieceMoves(
        const GameState& state,
        uint8_t square,
        std::vector<Move>& moves
    );

    // Genera todos los movimientos del jugador que tenga turno (futuro)
    static void generateAllMoves(
        const GameState& state,
        std::vector<Move>& moves
    );
};