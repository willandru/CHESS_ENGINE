#include "ChessGame.h"
#include "MoveFilter.h"
#include "MoveGenerator.h"
#include "MoveExecutor.h"
#include <iostream>

ChessGame::ChessGame()
{
    reset();
}

void ChessGame::reset()
{
    state.reset();

    whitePlayer.clearSelection();
    blackPlayer.clearSelection();

    waitingDestination = false;
    sourceSquare = 0;

    moves.clear();
}

void ChessGame::onSquareClicked(uint8_t square)
{
    HumanAgent& player =
        (state.getTurn() == PlayerSide::White)
        ? whitePlayer
        : blackPlayer;

    //==================================================
    // FIRST CLICK
    //==================================================
    if (!waitingDestination)
    {
        player.onSquareClicked(state, square);

        if (!player.hasSelection())
            return;

        sourceSquare = player.getSelectedSquare();
        moves.clear();

        // 1. PSEUDO MOVES
        MoveGenerator::generatePieceMoves(
            state,
            sourceSquare,
            moves
        );

        std::cout << "Pseudo moves: " << moves.size() << "\n";

        // 2. LEGAL FILTER
        MoveFilter::filterLegalMoves(state, moves);

        std::cout << "Legal moves: " << moves.size() << "\n";

        if (moves.empty())
        {
            player.clearSelection();
            waitingDestination = false;
            return;
        }

        waitingDestination = true;
        return;
    }

    //==================================================
    // SECOND CLICK
    //==================================================
    for (const Move& move : moves)
    {
        if (move.to != square)
            continue;

        MoveExecutor::execute(state, move);
        break;
    }

    player.clearSelection();
    moves.clear();
    waitingDestination = false;

    //==================================================
    // GAME STATE REPORT
    //==================================================
    auto status = MoveFilter::getGameStatus(state, state.getTurn());

    switch (status)
    {
        case MoveFilter::GameStateStatus::Check:
            std::cout << "STATE: CHECK\n";
            break;

        case MoveFilter::GameStateStatus::Checkmate:
            std::cout << "STATE: CHECKMATE\n";
            break;

        case MoveFilter::GameStateStatus::Stalemate:
            std::cout << "STATE: STALEMATE\n";
            break;

        default:
            std::cout << "STATE: NORMAL\n";
            break;
    }
}

const GameState& ChessGame::getGameState() const
{
    return state;
}

bool ChessGame::hasSelection() const
{
    if (state.getTurn() == PlayerSide::White)
        return whitePlayer.hasSelection();

    return blackPlayer.hasSelection();
}

uint8_t ChessGame::getSelectedSquare() const
{
    if (state.getTurn() == PlayerSide::White)
        return whitePlayer.getSelectedSquare();

    return blackPlayer.getSelectedSquare();
}

const std::vector<Move>& ChessGame::getMoves() const
{
    return moves;
}