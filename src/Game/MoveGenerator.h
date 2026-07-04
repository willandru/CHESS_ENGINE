#pragma once

#include <vector>
#include <cstdint>

#include "GameState.h"
#include "Move.h"

class MoveGenerator
{
public:

    static void generatePieceMoves(
        const GameState& state,
        uint8_t square,
        std::vector<Move>& moves
    );

    static void generateAllMoves(
        const GameState& state,
        std::vector<Move>& moves
    );

private:

    static bool isWhitePiece(Piece p);
    static bool isBlackPiece(Piece p);
};