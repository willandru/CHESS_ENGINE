#include "RandomAI.h"

#include "GameState.h"
#include "MoveGenerator.h"
#include "MoveFilter.h"

#include <cstdlib>
#include <ctime>

RandomAI::RandomAI()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void RandomAI::requestMove(const GameState& state)
{
    ready = false;

    std::vector<Move> moves;

    MoveGenerator::generateAllMoves(state, moves);
    MoveFilter::filterLegalMoves(state, moves);

    if (moves.empty())
        return;

    int idx = std::rand() % static_cast<int>(moves.size());

    selectedMove = moves[idx];
    ready = true;
}

bool RandomAI::hasMove() const
{
    return ready;
}

Move RandomAI::getMove() const
{
    return selectedMove;
}

void RandomAI::clear()
{
    ready = false;
}