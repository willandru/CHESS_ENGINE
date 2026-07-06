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

    promotionPending = false;
    promotionMoves.clear();

    inCheck = false;
    inCheckmate = false;
    inStalemate = false;

    aiTimer = 0.0f;
}

//====================================================

void ChessGame::update(float dt)
{
    if (promotionPending)
        return;

    Agent* current =
        (state.getTurn() == PlayerSide::White)
            ? player1.get()
            : player2.get();

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
    if (promotionPending)
        return;

    Agent* current =
        (state.getTurn() == PlayerSide::White)
            ? player1.get()
            : player2.get();

    if (!current->isHuman())
        return;

    current->onSquareClicked(square);

    //================================================
    // FIRST CLICK
    //================================================
    if (!waitingDestination)
    {
        selectedSquare = square;

        moves.clear();
        MoveGenerator::generatePieceMoves(state, selectedSquare, moves);
        MoveFilter::filterLegalMoves(state, moves);

        if (moves.empty())
        {
            selectedSquare = 0;
            return;
        }

        waitingDestination = true;
        return;
    }

    //================================================
    // SECOND CLICK
    //================================================
    for (const Move& m : moves)
    {
        if (m.to != square)
            continue;

        // PROMOTION TRIGGER
        if (m.isPromotion())
        {
            promotionPending = true;
            promotionMoves.clear();

            // generar 4 variantes manualmente
            Move base = m;

            base.setFlag(Move::PROMOTION);

            PlayerSide side = state.getTurn();

            Piece options[4] =
            {
                (side == PlayerSide::White ? WHITE_QUEEN  : BLACK_QUEEN),
                (side == PlayerSide::White ? WHITE_ROOK   : BLACK_ROOK),
                (side == PlayerSide::White ? WHITE_BISHOP : BLACK_BISHOP),
                (side == PlayerSide::White ? WHITE_KNIGHT : BLACK_KNIGHT)
            };

            for (int i = 0; i < 4; i++)
            {
                Move pm = base;
                pm.promo = options[i];
                promotionMoves.push_back(pm);
            }

            return;
        }

        MoveExecutor::execute(state, m);

        waitingDestination = false;
        selectedSquare = 0;
        moves.clear();

        updateGameStatus();
        return;
    }

    waitingDestination = false;
    selectedSquare = 0;
    moves.clear();
}

//====================================================

void ChessGame::onPromotionSelected(uint8_t option)
{
    if (!promotionPending)
        return;

    if (option >= promotionMoves.size())
        return;

    MoveExecutor::execute(state, promotionMoves[option]);

    promotionPending = false;
    promotionMoves.clear();

    waitingDestination = false;
    selectedSquare = 0;

    updateGameStatus();
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
        if (m.from != move.from || m.to != move.to)
            continue;

        if (m.isPromotion())
        {
            // IA elige dama automáticamente (simple y estable)
            Move autoMove = m;
            autoMove.promo =
                (state.getTurn() == PlayerSide::White)
                    ? WHITE_QUEEN
                    : BLACK_QUEEN;

            MoveExecutor::execute(state, autoMove);
        }
        else
        {
            MoveExecutor::execute(state, m);
        }

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

    if (inCheckmate) std::cout << "CHECKMATE\n";
    else if (inCheck) std::cout << "CHECK\n";
    else if (inStalemate) std::cout << "STALEMATE\n";
    else std::cout << "NORMAL\n";
}

//====================================================

const GameState& ChessGame::getGameState() const { return state; }

bool ChessGame::hasSelection() const { return waitingDestination; }
uint8_t ChessGame::getSelectedSquare() const { return selectedSquare; }
const std::vector<Move>& ChessGame::getMoves() const { return moves; }

bool ChessGame::isPromotionPending() const { return promotionPending; }
const std::vector<Move>& ChessGame::getPromotionMoves() const { return promotionMoves; }