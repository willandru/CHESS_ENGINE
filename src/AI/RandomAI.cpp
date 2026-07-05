#include "RandomAI.h"

#include "AgentRegistry.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

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
    //------------------------------------------------
    // Build depth-1 tree
    //------------------------------------------------

    tree.build(state, 1);

    const DecisionNode& root = tree.getRoot();

    std::cout << "[DEBUG] Children count: "
              << root.children.size()
              << std::endl;

    if (root.children.empty())
        return false;

    //------------------------------------------------
    // Pick one child randomly
    //------------------------------------------------

    int index =
        std::rand() % static_cast<int>(root.children.size());

    move = root.children[index].move;

    return true;
}

//====================================================
// REGISTRATION
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
            });

        return true;
    }();
}