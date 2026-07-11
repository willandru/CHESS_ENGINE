#include "ChessGame.h"

#include "MoveExecutor.h"
#include "MoveFilter.h"
#include "MoveGenerator.h"
#include "AgentConfig.h"

#include "RLAgentAI.h"

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
    promotionSide = 0;

    inCheck = false;
    inCheckmate = false;
    inStalemate = false;

    pendingRestart = false;

    aiTimer = 0.0f;
}

//====================================================

void ChessGame::update(float dt)
{

    if(pendingRestart)
    {
        std::cout
            << "NEW GAME"
            << std::endl;

        reset();

        return;
    }

    if (promotionPending)
        return;

    if (inCheckmate || inStalemate)
        return;

    Agent* current =
        (state.getTurn() == PlayerSide::White)
            ? player1.get()
            : player2.get();

    if (!current || current->isHuman())
        return;

    aiTimer += dt;

    if (aiTimer < AI_DELAY)
        return;

    aiTimer = 0.0f;

    playCurrentPlayer();
}

//====================================================


void ChessGame::cancelSelection()
{
    waitingDestination = false;

    selectedSquare = 0;

    moves.clear();

    std::cout
        << "SELECTION CANCELLED"
        << std::endl;
}

void ChessGame::onSquareClicked(uint8_t square)
{
    if (promotionPending)
        return;

    if (inCheckmate || inStalemate)
        return;

    Agent* current =
        (state.getTurn() == PlayerSide::White)
            ? player1.get()
            : player2.get();

            

    std::cout
        << "CLICK RECEIVED: "
        << (int)square
        << std::endl;


    std::cout
        << "TURN: "
        << (state.getTurn() == PlayerSide::White ? "WHITE" : "BLACK")
        << std::endl;


            if(current)
    {
        std::cout
            << "IS HUMAN: "
            << current->isHuman()
            << std::endl;
    }
    else
    {
        std::cout
            << "CURRENT PLAYER NULL"
            << std::endl;
    }


    if (!current || !current->isHuman())
        return;

    current->onSquareClicked(square);

    //------------------------------------------------
    // FIRST CLICK
    //------------------------------------------------
    if (!waitingDestination)
    {
        selectedSquare = square;

        moves.clear();
        MoveGenerator::generatePieceMoves(state, selectedSquare, moves);
        MoveFilter::filterLegalMoves(state, moves);

        if (moves.empty())
        {
            waitingDestination = false;
            selectedSquare = 0;
            return;
        }

        waitingDestination = true;
        return;
    }

    //------------------------------------------------
    // SECOND CLICK
    //------------------------------------------------

    // ¿Es un movimiento legal?
    for (const Move& m : moves)
    {
        if (m.to != square)
            continue;

        //------------------------------------------------
        // PROMOTION
        //------------------------------------------------
        if (m.isPromotion())
        {
            promotionPending = true;
            promotionMoves.clear();

            promotionSide =
                (state.getTurn() == PlayerSide::White)
                    ? 0
                    : 1;

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

        std::cout
            << "Human: "
            << GameState::squareToNotation(m.from)
            << " -> "
            << GameState::squareToNotation(m.to)
            << '\n';

        MoveExecutor::execute(state, m);

        waitingDestination = false;
        selectedSquare = 0;
        moves.clear();

        updateGameStatus();
        return;
    }

    //------------------------------------------------
    // NO ERA UN MOVIMIENTO.
    // ¿LA CASILLA CONTIENE OTRA PIEZA JUGABLE?
    //------------------------------------------------

    std::vector<Move> newMoves;

    MoveGenerator::generatePieceMoves(state, square, newMoves);
    MoveFilter::filterLegalMoves(state, newMoves);

    if (!newMoves.empty())
    {
        selectedSquare = square;
        moves = std::move(newMoves);
        waitingDestination = true;
        return;
    }

    //------------------------------------------------
    // CLICK EN CASILLA VACÍA O PIEZA ENEMIGA
    //------------------------------------------------

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

    if (!current)
        return;

    Move move;

    if (!current->decide(state, move))
        return;

    std::vector<Move> legal;
    MoveGenerator::generateAllMoves(state, legal);
    MoveFilter::filterLegalMoves(state, legal);

    for (const Move& m : legal)
    {
        if (m.from != move.from)
            continue;

        if (m.to != move.to)
            continue;

        // Si ambos son promociones, deben promocionar
        // a la misma pieza.
        if (m.isPromotion())
        {
            if (m.promo != move.promo)
                continue;
        }

        MoveExecutor::execute(state, m);


        current->observe(state);


        updateGameStatus();
        return;
    }
}

//====================================================

void ChessGame::updateGameStatus()
{
    PlayerSide side = state.getTurn();

    //------------------------------------------------
    // 50-MOVE RULE
    //------------------------------------------------

    if (state.getHalfMoveClock() >= 100)
    {
        std::cout
            << "50-MOVE RULE: STALEMATE"
            << std::endl;

        inCheck = false;
        inCheckmate = false;
        inStalemate = true;
        return;

    }

    //------------------------------------------------
    // NORMAL STATUS
    //------------------------------------------------

    inCheck =
        MoveFilter::isKingInCheck(state, side);

    inCheckmate =
        MoveFilter::isCheckmate(state, side);

    inStalemate =
        MoveFilter::isStalemate(state, side);




    if (inCheckmate)
    {
        std::cout << "CHECKMATE\n";


        //------------------------------------------------
        // Notify AI episode result
        //------------------------------------------------

        Agent* winner =
            (state.getTurn() == PlayerSide::White)
            ? player2.get()
            : player1.get();


        if(auto rl =
            dynamic_cast<RLAgentAI*>(winner))
        {
            rl->finishGame(true);
        }



        Agent* loser =
            (state.getTurn() == PlayerSide::White)
            ? player1.get()
            : player2.get();


        if(auto rl =
            dynamic_cast<RLAgentAI*>(loser))
        {
            rl->finishGame(false);
        }

    pendingRestart = true;

    }
    else if (inCheck)
    {
        std::cout << "CHECK\n";
    }
    else if (inStalemate)
    {
        pendingRestart = true;
        std::cout << "STALEMATE\n";
    }
    else
    {
        std::cout << "NORMAL\n";
    }
}

//====================================================
// POSITION ANALYSIS
//====================================================

void ChessGame::analyzeCurrentPosition()
{

    analyzer.analyze(
        state,
        1,
        selectedSquare);
}

//====================================================

const GameState& ChessGame::getGameState() const { return state; }

bool ChessGame::hasSelection() const { return waitingDestination; }

uint8_t ChessGame::getSelectedSquare() const { return selectedSquare; }

const std::vector<Move>& ChessGame::getMoves() const { return moves; }

bool ChessGame::isPromotionPending() const { return promotionPending; }

const std::vector<Move>& ChessGame::getPromotionMoves() const { return promotionMoves; }

uint8_t ChessGame::getPromotionSelectedSide() const { return promotionSide; }