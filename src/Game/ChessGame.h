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

    //------------------------------------------------
    // GAME
    //------------------------------------------------

    void reset();
    void update(float dt);

    //------------------------------------------------
    // INPUT
    //------------------------------------------------

    void onSquareClicked(uint8_t square);
    void onPromotionSelected(uint8_t option);

    //------------------------------------------------
    // STATE
    //------------------------------------------------

    const GameState& getGameState() const;

    //------------------------------------------------
    // UI
    //------------------------------------------------

    bool hasSelection() const;
    uint8_t getSelectedSquare() const;
    const std::vector<Move>& getMoves() const;

    //------------------------------------------------
    // PROMOTION
    //------------------------------------------------

    bool isPromotionPending() const;
    const std::vector<Move>& getPromotionMoves() const;

private:

    void updateGameStatus();
    void playCurrentPlayer();
    void bindPlayers();

private:

    //------------------------------------------------
    // GAME STATE
    //------------------------------------------------

    GameState state;

    //------------------------------------------------
    // PLAYERS
    //------------------------------------------------

    std::unique_ptr<Agent> player1;
    std::unique_ptr<Agent> player2;

    //------------------------------------------------
    // SELECTION
    //------------------------------------------------

    bool waitingDestination = false;
    uint8_t selectedSquare = 0;
    std::vector<Move> moves;

    //------------------------------------------------
    // PROMOTION
    //------------------------------------------------

    bool promotionPending = false;
    std::vector<Move> promotionMoves;

    //------------------------------------------------
    // GAME STATUS
    //------------------------------------------------

    bool inCheck = false;
    bool inCheckmate = false;
    bool inStalemate = false;

    //------------------------------------------------
    // AI
    //------------------------------------------------

    float aiTimer = 0.0f;

    static constexpr float AI_DELAY = 0.1f;
};