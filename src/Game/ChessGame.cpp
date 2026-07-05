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

    whitePlayer.clear();

    waitingDestination = false;
    selectedSquare = 0;
    moves.clear();

    blackAI.clear();

    inCheck = false;
    inCheckmate = false;
    inStalemate = false;
}

//====================================================
// UPDATE
//====================================================

void ChessGame::update(float dt)
{
    (void)dt;
}

//====================================================
// MAIN INPUT (ONLY HUMAN INPUT)
//====================================================

void ChessGame::onSquareClicked(uint8_t square)
{
    if (state.getTurn() != PlayerSide::White)
        return;

    HumanAgent& player = whitePlayer;

    //------------------------------------------------
    // FIRST CLICK (SELECT PIECE)
    //------------------------------------------------

    if (!waitingDestination)
    {
        player.onSquareClicked(square);

        if (!player.hasClick())
            return;

        selectedSquare = player.getClickedSquare();

        player.clear();

        moves.clear();

        MoveGenerator::generatePieceMoves(
            state,
            selectedSquare,
            moves
        );

        MoveFilter::filterLegalMoves(
            state,
            moves
        );

        if (moves.empty())
        {
            selectedSquare = 0;
            return;
        }

        waitingDestination = true;
        return;
    }

    //------------------------------------------------
    // SECOND CLICK (EXECUTE MOVE)
    //------------------------------------------------

    bool executed = false;

    for (const Move& move : moves)
    {
        if (move.to == square)
        {
            MoveExecutor::execute(state, move);
            executed = true;
            break;
        }
    }

    moves.clear();

    waitingDestination = false;
    selectedSquare = 0;

    if (!executed)
        return;

    updateGameStatus();

    playBlackTurnIfNeeded();
}

//====================================================
// BLACK AI TURN
//====================================================

void ChessGame::playBlackTurnIfNeeded()
{
    if (state.getTurn() != PlayerSide::Black)
        return;

    blackAI.requestMove(state);

    if (blackAI.hasMove())
    {
        MoveExecutor::execute(
            state,
            blackAI.getMove()
        );
    }

    blackAI.clear();

    updateGameStatus();
}

//====================================================
// STATUS UPDATE
//====================================================

void ChessGame::updateGameStatus()
{
    PlayerSide side = state.getTurn();

    inCheck = MoveFilter::isKingInCheck(state, side);
    inCheckmate = MoveFilter::isCheckmate(state, side);
    inStalemate = MoveFilter::isStalemate(state, side);

    if (inCheckmate)
        std::cout << "STATE: CHECKMATE\n";
    else if (inCheck)
        std::cout << "STATE: CHECK\n";
    else if (inStalemate)
        std::cout << "STATE: STALEMATE\n";
    else
        std::cout << "STATE: NORMAL\n";
}

//====================================================
// GETTERS
//====================================================

const GameState& ChessGame::getGameState() const
{
    return state;
}

bool ChessGame::hasSelection() const
{
    return waitingDestination;
}

uint8_t ChessGame::getSelectedSquare() const
{
    return selectedSquare;
}

const std::vector<Move>& ChessGame::getMoves() const
{
    return moves;
}

bool ChessGame::isCheck() const
{
    return inCheck;
}

bool ChessGame::isCheckmate() const
{
    return inCheckmate;
}

bool ChessGame::isStalemate() const
{
    return inStalemate;
}