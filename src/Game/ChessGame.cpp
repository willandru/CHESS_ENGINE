#include "ChessGame.h"

#include "MoveExecutor.h"
#include "MoveFilter.h"
#include "MoveGenerator.h"
#include "AgentConfig.h"

#include <iostream>

//====================================================

ChessGame::ChessGame()
{
    bindPlayers();
    reset();
}

//====================================================

void ChessGame::bindPlayers()
{
    player1 = AgentConfig::getPlayer1();
    player2 = AgentConfig::getPlayer2();
}

//====================================================

void ChessGame::reset()
{
    state.reset();

    waitingDestination = false;
    selectedSquare = 0;
    moves.clear();

    inCheck = false;
    inCheckmate = false;
    inStalemate = false;
}

//====================================================

void ChessGame::update(float dt)
{
    (void)dt;
    playCurrentPlayer();
}

//====================================================

void ChessGame::onSquareClicked(uint8_t square)
{
    Agent* current =
        (state.getTurn() == PlayerSide::White)
            ? player1.get()
            : player2.get();

    if (!current->isHuman())
        return;

    current->onSquareClicked(square);

    // =========================
    // FIRST CLICK: SELECT PIECE
    // =========================
    if (!waitingDestination)
    {
        selectedSquare = square;

        moves.clear();
        MoveGenerator::generatePieceMoves(state, selectedSquare, moves);
        MoveFilter::filterLegalMoves(state, moves);

        if (moves.empty())
        {
            // pieza sin jugadas válidas → no selección
            selectedSquare = 0;
            waitingDestination = false;
            return;
        }

        waitingDestination = true;
        return;
    }

    // =========================
    // SECOND CLICK: EXECUTE ONLY LEGAL MOVE
    // =========================

    for (const Move& m : moves)
    {
        if (m.to == square)
        {
            MoveExecutor::execute(state, m);
            updateGameStatus();

            waitingDestination = false;
            selectedSquare = 0;
            moves.clear();
            return;
        }
    }

    // click inválido → reset seguro
    waitingDestination = false;
    selectedSquare = 0;
    moves.clear();
}

//====================================================

void ChessGame::playCurrentPlayer()
{
    Agent* current =
        (state.getTurn() == PlayerSide::White)
            ? player1.get()
            : player2.get();

    Move move;

    if (!current->decide(state, move))
        return;

    // 🔥 CRÍTICO: validar contra moves generados si quieres seguridad extra
    std::vector<Move> legal;
    MoveGenerator::generateAllMoves(state, legal);
    MoveFilter::filterLegalMoves(state, legal);

    bool ok = false;
    for (const Move& m : legal)
    {
        if (m.from == move.from && m.to == move.to)
        {
            ok = true;
            break;
        }
    }

    if (!ok)
        return;

    MoveExecutor::execute(state, move);
    updateGameStatus();
}

//====================================================

void ChessGame::updateGameStatus()
{
    PlayerSide side = state.getTurn();

    inCheck = MoveFilter::isKingInCheck(state, side);
    inCheckmate = MoveFilter::isCheckmate(state, side);
    inStalemate = MoveFilter::isStalemate(state, side);

    if (inCheckmate)
        std::cout << "CHECKMATE\n";
    else if (inCheck)
        std::cout << "CHECK\n";
    else if (inStalemate)
        std::cout << "STALEMATE\n";
    else
        std::cout << "NORMAL\n";
}

//====================================================

const GameState& ChessGame::getGameState() const
{
    return state;
}

//====================================================

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