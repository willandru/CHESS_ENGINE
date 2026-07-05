#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "GameState.h"
#include "Agent.h"
#include "Move.h"

class ChessGame
{
public:

    ChessGame();

    void reset();
    void update(float dt);

    void onSquareClicked(uint8_t square);

    const GameState& getGameState() const;

    // ===== UI LEGACY (para que compile renderer) =====
    bool hasSelection() const;
    uint8_t getSelectedSquare() const;
    const std::vector<Move>& getMoves() const;

private:

    void updateGameStatus();
    void playCurrentPlayer();
    void bindPlayers();

private:

    GameState state;

    std::unique_ptr<Agent> player1;
    std::unique_ptr<Agent> player2;

    // ===== UI STATE (mínimo necesario) =====
    bool waitingDestination = false;
    uint8_t selectedSquare = 0;
    std::vector<Move> moves;

    bool inCheck = false;
    bool inCheckmate = false;
    bool inStalemate = false;
};