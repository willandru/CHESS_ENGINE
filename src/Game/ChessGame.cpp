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

    waitingDestination = false;
    sourceSquare = 0;
    moves.clear();

    blackAI.clear();

    inCheck = false;
    inCheckmate = false;
    inStalemate = false;
}

//====================================================
// MAIN INPUT (ONLY HUMAN INPUT)
//====================================================
void ChessGame::onSquareClicked(uint8_t square)
{
    if (state.getTurn() != PlayerSide::White)
        return;

    HumanAgent& player = whitePlayer;

    //================================================
    // FIRST CLICK (SELECT PIECE)
    //================================================
    if (!waitingDestination)
    {
        player.onSquareClicked(state, square);

        if (!player.hasSelection())
            return;

        sourceSquare = player.getSelectedSquare();
        moves.clear();

        MoveGenerator::generatePieceMoves(state, sourceSquare, moves);
        MoveFilter::filterLegalMoves(state, moves);

        if (moves.empty())
        {
            player.clearSelection();
            return;
        }

        waitingDestination = true;
        return;
    }

    //================================================
    // SECOND CLICK (EXECUTE MOVE)
    //================================================
    for (const Move& move : moves)
    {
        if (move.to == square)
        {
            MoveExecutor::execute(state, move);
            break;
        }
    }

    player.clearSelection();
    moves.clear();
    waitingDestination = false;

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
        MoveExecutor::execute(state, blackAI.getMove());
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
    return whitePlayer.hasSelection();
}

uint8_t ChessGame::getSelectedSquare() const
{
    return whitePlayer.getSelectedSquare();
}

const std::vector<Move>& ChessGame::getMoves() const
{
    return moves;
}