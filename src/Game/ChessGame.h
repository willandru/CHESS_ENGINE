#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "GameState.h"
#include "Agent.h"
#include "Move.h"
#include "ChessAnalyzer.h"

class ChessGame
{
public:

    ChessGame();

    //------------------------------------------------
    // GAME LOOP
    //------------------------------------------------
    void reset();
    void update(float dt);

    //------------------------------------------------
    // INPUT
    //------------------------------------------------
    void onSquareClicked(uint8_t square);
    void onPromotionSelected(uint8_t option);

    //------------------------------------------------
    // STATE ACCESS
    //------------------------------------------------
    const GameState& getGameState() const;

    //------------------------------------------------
    // UI SELECTION
    //------------------------------------------------
    bool hasSelection() const;
    uint8_t getSelectedSquare() const;
    const std::vector<Move>& getMoves() const;

    //------------------------------------------------
    // PROMOTION UI
    //------------------------------------------------
    bool isPromotionPending() const;
    const std::vector<Move>& getPromotionMoves() const;

    // Snapshot del lado que promociona
    uint8_t getPromotionSelectedSide() const;

private:

    //------------------------------------------------
    // INTERNAL LOGIC
    //------------------------------------------------
    void updateGameStatus();
    void playCurrentPlayer();
    void bindPlayers();
    //------------------------------------------------
    // POSITION ANALYSIS
    //------------------------------------------------

    void analyzeCurrentPosition();

private:

    //------------------------------------------------
    // CORE GAME STATE
    //------------------------------------------------
    GameState state;

    //------------------------------------------------
    // POSITION ANALYZER
    //------------------------------------------------
    ChessAnalyzer analyzer;

    //------------------------------------------------
    // PLAYERS (AI / HUMAN)
    //------------------------------------------------
    std::unique_ptr<Agent> player1;
    std::unique_ptr<Agent> player2;

    //------------------------------------------------
    // SELECTION STATE
    //------------------------------------------------
    bool waitingDestination = false;
    uint8_t selectedSquare = 0;
    std::vector<Move> moves;

    //------------------------------------------------
    // PROMOTION STATE
    //------------------------------------------------
    bool promotionPending = false;
    uint8_t promotionSide = 0; // 0 = white, 1 = black
    std::vector<Move> promotionMoves;

    //------------------------------------------------
    // GAME STATUS FLAGS
    //------------------------------------------------
    bool inCheck = false;
    bool inCheckmate = false;
    bool inStalemate = false;

    //------------------------------------------------
    // AI TIMING CONTROL
    //------------------------------------------------
    float aiTimer = 0.0f;

    static constexpr float AI_DELAY = 0.2f;


};