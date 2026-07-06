#include "ChessGame.h"

#include "MoveExecutor.h"
#include "MoveFilter.h"
#include "MoveGenerator.h"
#include "AgentConfig.h"

#include <iostream>

//====================================================

ChessGame::ChessGame()
{
    AgentConfig::load();
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
    Agent* current =
        (state.getTurn() == PlayerSide::White)
            ? player1.get()
            : player2.get();

    // El humano no necesita temporizador.
    if (current->isHuman())
        return;
    
    if (inCheckmate || inStalemate)
    return;

    aiTimer += dt;

    if (aiTimer < AI_DELAY)
        return;

    aiTimer = 0.0f;

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
            selectedSquare = 0;
            waitingDestination = false;
            return;
        }

        waitingDestination = true;
        return;
    }

    // =========================
    // SECOND CLICK: EXECUTE MOVE
    // =========================

    for (const Move& m : moves)
    {
        if (m.to != square)
            continue;

        // Promoción automática a dama.
        if (m.isPromotion() &&
            m.promo != WHITE_QUEEN &&
            m.promo != BLACK_QUEEN)
        {
            continue;
        }

        MoveExecutor::execute(state, m);

        aiTimer = 0.0f;
        updateGameStatus();

        waitingDestination = false;
        selectedSquare = 0;
        moves.clear();
        return;
    }

    // Click inválido
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

    std::vector<Move> legal;
    MoveGenerator::generateAllMoves(state, legal);
    MoveFilter::filterLegalMoves(state, legal);

    for (const Move& m : legal)
    {
        if (m.from != move.from ||
            m.to != move.to)
        {
            continue;
        }

        // Promoción automática a dama.
        if (m.isPromotion() &&
            m.promo != WHITE_QUEEN &&
            m.promo != BLACK_QUEEN)
        {
            continue;
        }

        MoveExecutor::execute(state, m);
        updateGameStatus();
        return;
    }
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