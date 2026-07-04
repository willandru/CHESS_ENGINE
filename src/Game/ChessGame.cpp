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

    inCheck = false;
    inCheckmate = false;
    inStalemate = false;
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

        MoveGenerator::generatePieceMoves(
            state,
            sourceSquare,
            moves
        );

        MoveFilter::filterLegalMoves(state, moves);

        if (moves.empty())
        {
            player.clearSelection();
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
    // UPDATE GAME STATE
    //==================================================
    updateGameStatus();

    if (inCheckmate)
        std::cout << "STATE: CHECKMATE\n";
    else if (inCheck)
        std::cout << "STATE: CHECK\n";
    else if (inStalemate)
        std::cout << "STATE: STALEMATE\n";
    else
        std::cout << "STATE: NORMAL\n";
}

void ChessGame::updateGameStatus()
{
    PlayerSide side = state.getTurn();

    inCheck = MoveFilter::isKingInCheck(state, side);
    inCheckmate = MoveFilter::isCheckmate(state, side);
    inStalemate = MoveFilter::isStalemate(state, side);
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