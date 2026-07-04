#include "ChessGame.h"

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

    //--------------------------------------------------
    // PRIMER CLICK
    //--------------------------------------------------

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

        if (moves.empty())
        {
            player.clearSelection();
            return;
        }

        waitingDestination = true;

        std::cout
            << "Generated "
            << moves.size()
            << " moves.\n";

        return;
    }

    //--------------------------------------------------
    // SEGUNDO CLICK
    //--------------------------------------------------

    for (const Move& move : moves)
    {
        if (move.to != square)
            continue;

        MoveExecutor::execute(state, move);

        std::cout
            << "Move executed: "
            << (int)move.from
            << " -> "
            << (int)move.to
            << '\n';

        break;
    }

    player.clearSelection();

    moves.clear();

    waitingDestination = false;
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