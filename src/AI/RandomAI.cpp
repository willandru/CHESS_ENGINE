#include "RandomAI.h"

#include "MoveGenerator.h"
#include "MoveFilter.h"

#include <cstdlib>
#include <ctime>

RandomAI::RandomAI()
{
    std::srand(
        static_cast<unsigned int>(
            std::time(nullptr)
        )
    );
}

bool RandomAI::decide(
    const GameState& state,
    Move& move)
{
    std::vector<Move> moves;

    MoveGenerator::generateAllMoves(
        state,
        moves
    );

    MoveFilter::filterLegalMoves(
        state,
        moves
    );

    if (moves.empty())
        return false;

    int index =
        std::rand() %
        static_cast<int>(moves.size());

    move = moves[index];

    return true;
}