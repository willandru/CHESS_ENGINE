#include "CaptureAI.h"
#include "MoveGenerator.h"
#include "MoveFilter.h"

#include <cstdlib>
#include <ctime>

CaptureAI::CaptureAI()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void CaptureAI::requestMove(const GameState& state)
{
    ready = false;

    std::vector<Move> moves;
    MoveGenerator::generateAllMoves(state, moves);
    MoveFilter::filterLegalMoves(state, moves);

    if (moves.empty())
        return;

    // 1. buscar capturas primero
    std::vector<Move> captures;

    for (const Move& m : moves)
    {
        if (m.captured != EMPTY)
            captures.push_back(m);
    }

    const std::vector<Move>& pool =
        captures.empty() ? moves : captures;

    selectedMove = pool[std::rand() % pool.size()];
    ready = true;
}

bool CaptureAI::hasMove() const
{
    return ready;
}

Move CaptureAI::getMove() const
{
    return selectedMove;
}

void CaptureAI::clear()
{
    ready = false;
}