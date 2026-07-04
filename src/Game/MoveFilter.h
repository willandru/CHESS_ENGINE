#pragma once

#include <vector>
#include <cstdint>

#include "GameState.h"
#include "Move.h"

class MoveFilter
{
public:

    enum class GameStateStatus
    {
        Normal,
        Check,
        Checkmate,
        Stalemate
    };

    static void filterLegalMoves(
        const GameState& state,
        std::vector<Move>& moves);

    static bool isKingInCheck(
        const GameState& state,
        PlayerSide side);

    static bool isCheckmate(
        const GameState& state,
        PlayerSide side);

    static bool isStalemate(
        const GameState& state,
        PlayerSide side);

    static GameStateStatus getGameStatus(
        const GameState& state,
        PlayerSide side);

private:

    static bool isSquareAttacked(
        const GameState& state,
        uint8_t square,
        PlayerSide attackerSide);

    static uint8_t findKing(
        const GameState& state,
        PlayerSide side);
};