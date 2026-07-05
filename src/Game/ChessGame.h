#pragma once

#include <vector>
#include <cstdint>

#include "GameState.h"
#include "HumanAgent.h"
#include "RandomAI.h"
#include "Move.h"

class ChessGame
{
public:

    ChessGame();

    //------------------------------------------------
    // GAME
    //------------------------------------------------

    void reset();
    void update(float dt);

    //------------------------------------------------
    // INPUT
    //------------------------------------------------

    void onSquareClicked(uint8_t square);

    //------------------------------------------------
    // GETTERS
    //------------------------------------------------

    const GameState& getGameState() const;

    bool hasSelection() const;
    uint8_t getSelectedSquare() const;

    const std::vector<Move>& getMoves() const;

    bool isCheck() const;
    bool isCheckmate() const;
    bool isStalemate() const;

private:

    //------------------------------------------------
    // GAME STATE
    //------------------------------------------------

    GameState state;

    //------------------------------------------------
    // PLAYERS
    //------------------------------------------------

    HumanAgent whitePlayer;
    RandomAI   blackAI;

    //------------------------------------------------
    // HUMAN INTERACTION
    //------------------------------------------------

    bool waitingDestination = false;

    uint8_t selectedSquare = 0;

    std::vector<Move> moves;

    //------------------------------------------------
    // GAME STATUS
    //------------------------------------------------

    bool inCheck = false;
    bool inCheckmate = false;
    bool inStalemate = false;

    //------------------------------------------------
    // INTERNAL
    //------------------------------------------------

    void updateGameStatus();
    void playBlackTurnIfNeeded();
};