#include "ChessGame.h"
#include "MoveGenerator.h"
#include "MoveFilter.h"
#include "MoveExecutor.h"

#include <iostream>

ChessGame::ChessGame()
{
    reset();
}

void ChessGame::reset()
{
    state.reset();

    moves.clear();

    inCheck = false;
    inCheckmate = false;
    inStalemate = false;

    aiTimer = 0.0f;
}

//====================================================
// UPDATE CON DELTA TIME
//====================================================
void ChessGame::update(float dt)
{
    aiTimer += dt;

    if (aiTimer < aiDelay)
        return;

    aiTimer = 0.0f;

    playAITurn();
}

//====================================================
// AI vs AI TURN
//====================================================
void ChessGame::playAITurn()
{
    if (state.getTurn() == PlayerSide::White)
    {
        whiteAI.requestMove(state);

        if (whiteAI.hasMove())
            MoveExecutor::execute(state, whiteAI.getMove());
    }
    else
    {
        blackAI.requestMove(state);

        if (blackAI.hasMove())
            MoveExecutor::execute(state, blackAI.getMove());
    }

    updateGameStatus();
}

//====================================================
void ChessGame::updateGameStatus()
{
    PlayerSide side = state.getTurn();

    inCheck = MoveFilter::isKingInCheck(state, side);
    inCheckmate = MoveFilter::isCheckmate(state, side);
    inStalemate = MoveFilter::isStalemate(state, side);
}

//====================================================
// UI SAFE (no rompe renderer)
//====================================================
const GameState& ChessGame::getGameState() const { return state; }

bool ChessGame::hasSelection() const { return false; }
uint8_t ChessGame::getSelectedSquare() const { return 0; }
const std::vector<Move>& ChessGame::getMoves() const { return moves; }

bool ChessGame::isCheck() const { return inCheck; }
bool ChessGame::isCheckmate() const { return inCheckmate; }
bool ChessGame::isStalemate() const { return inStalemate; }

void ChessGame::onSquareClicked(uint8_t square)
{
    (void)square;
}