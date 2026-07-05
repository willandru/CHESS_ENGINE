#include "CaptureAI.h"

#include "MoveGenerator.h"
#include "MoveFilter.h"
#include "AgentRegistry.h"

#include <cstdlib>
#include <ctime>

CaptureAI::CaptureAI()
{
    std::srand(
        static_cast<unsigned int>(
            std::time(nullptr)
        )
    );
}

//====================================================
// AGENT
//====================================================

bool CaptureAI::isHuman() const
{
    return false;
}

bool CaptureAI::decide(
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

    //------------------------------------------------
    // Preferir capturas
    //------------------------------------------------

    std::vector<Move> captures;

    for (const Move& m : moves)
    {
        if (m.isCapture())
            captures.push_back(m);
    }

    const std::vector<Move>& pool =
        captures.empty()
            ? moves
            : captures;

    move =
        pool[
            std::rand() %
            static_cast<int>(pool.size())
        ];

    return true;
}


namespace
{
    bool registered = []()
    {
        AgentRegistry::registerAgent("CaptureAI",
            []() -> std::unique_ptr<Agent>
            {
                return std::make_unique<CaptureAI>();
            });

        return true;
    }();
}
