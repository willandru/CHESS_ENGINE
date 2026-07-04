#pragma once

#include <vector>
#include <cstdint>

#include "GameState.h"
#include "HumanAgent.h"
#include "MoveGenerator.h"
#include "MoveExecutor.h"

class ChessGame
{
public:

    ChessGame();

    void reset();

    void onSquareClicked(uint8_t square);

    const GameState& getGameState() const;

    bool hasSelection() const;
    uint8_t getSelectedSquare() const;

    const std::vector<Move>& getMoves() const;

private:

    GameState state;

    HumanAgent whitePlayer;
    HumanAgent blackPlayer;

    bool waitingDestination;

    uint8_t sourceSquare;

    std::vector<Move> moves;
};