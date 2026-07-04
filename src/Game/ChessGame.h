#pragma once

#include <vector>
#include <cstdint>

#include "GameState.h"
#include "RandomAI.h"
#include "CaptureAI.h"
#include "Move.h"

class ChessGame
{
public:
    ChessGame();

    void reset();
    void update(float dt);   // <-- IMPORTANTE

    const GameState& getGameState() const;

    bool hasSelection() const;
    uint8_t getSelectedSquare() const;
    const std::vector<Move>& getMoves() const;

    bool isCheck() const;
    bool isCheckmate() const;
    bool isStalemate() const;

    void onSquareClicked(uint8_t square);

private:

    GameState state;

    RandomAI whiteAI;
    CaptureAI blackAI;

    std::vector<Move> moves;

    bool inCheck = false;
    bool inCheckmate = false;
    bool inStalemate = false;

    void updateGameStatus();
    void playAITurn();

    // ===== TIMER CONTROL =====
    float aiTimer = 0.0f;
    const float aiDelay = 0.3f;
};