#include "RandomAI.h"

#include "MoveGenerator.h"
#include "MoveFilter.h"
#include "AgentRegistry.h"

#include <cstdlib>
#include <ctime>

RandomAI::RandomAI()
{
    static bool seeded = false;
    if (!seeded)
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }
}

//====================================================
// AGENT
//====================================================

bool RandomAI::isHuman() const
{
    return false;
}

bool RandomAI::decide(
    const GameState& state,
    Move& move)
{
    std::vector<Move> moves;

    MoveGenerator::generateAllMoves(state, moves);
    MoveFilter::filterLegalMoves(state, moves);

    if (moves.empty())
        return false;

    int index =
        std::rand() % static_cast<int>(moves.size());

    move = moves[index];

    return true;
}

//====================================================
// REGISTRATION (MUY IMPORTANTE)
//====================================================

namespace
{
    const bool registered = []()
    {
        AgentRegistry::registerAgent(
            "RandomAI",
            []() -> std::unique_ptr<Agent>
            {
                return std::make_unique<RandomAI>();
            }
        );

        return true;
    }();
}