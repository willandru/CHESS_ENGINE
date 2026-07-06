#include "DefenseAI.h"

#include "AgentRegistry.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

DefenseAI::DefenseAI()
{
    static bool seeded = false;

    if (!seeded)
    {
        std::srand(
            static_cast<unsigned>(
                std::time(nullptr)));

        seeded = true;
    }
}

//====================================================
// AGENT
//====================================================

bool DefenseAI::isHuman() const
{
    return false;
}

bool DefenseAI::decide(
    const GameState& state,
    Move& move)
{
    //------------------------------------------------
    // Build search tree
    //
    // Depth 0 : current position
    // Depth 1 : our move
    // Depth 2 : opponent reply
    //------------------------------------------------

    tree.build(state, 2);

    const DecisionNode& root =
        tree.getRoot();

    if (root.children.empty())
        return false;

    //------------------------------------------------
    // Analysis
    //------------------------------------------------

    std::vector<int> safeMoves;

    uint32_t analysedEnemyReplies = 0;
    uint32_t dangerousMoves = 0;

    //------------------------------------------------
    // Analyse every legal move
    //------------------------------------------------

    for (size_t i = 0;
         i < root.children.size();
         ++i)
    {
        const DecisionNode& myMove =
            root.children[i];

        //------------------------------------------------
        // No opponent replies
        //------------------------------------------------

        if (myMove.children.empty())
        {
            safeMoves.push_back(
                static_cast<int>(i));

            continue;
        }

        //------------------------------------------------
        // Check every opponent reply
        //------------------------------------------------

        bool safe = true;

        for (const DecisionNode& enemyReply :
             myMove.children)
        {
            ++analysedEnemyReplies;

            if (enemyReply.move.isCapture())
            {
                safe = false;
                break;
            }
        }

        if (safe)
        {
            safeMoves.push_back(
                static_cast<int>(i));
        }
        else
        {
            ++dangerousMoves;
        }
    }

    //------------------------------------------------
    // Choose move
    //------------------------------------------------

    const char* decision = "RANDOM";

    if (!safeMoves.empty())
    {
        int idx =
            safeMoves[
                std::rand() %
                safeMoves.size()
            ];

        move =
            root.children[idx].move;

        decision = "SAFE";
    }
    else
    {
        int idx =
            std::rand() %
            static_cast<int>(
                root.children.size());

        move =
            root.children[idx].move;
    }

    //------------------------------------------------
    // Debug
    //------------------------------------------------

    std::cout
        << "\n========== DefenseAI ==========\n";

    std::cout
        << "Visited nodes          : "
        << tree.getVisitedNodes()
        << '\n';

    std::cout
        << "Tree depth             : "
        << tree.getMaxDepth()
        << '\n';

    std::cout
        << "Root moves analysed    : "
        << root.children.size()
        << '\n';

    std::cout
        << "Enemy replies analysed : "
        << analysedEnemyReplies
        << '\n';

    std::cout
        << "Safe moves             : "
        << safeMoves.size()
        << '\n';

    std::cout
        << "Dangerous moves        : "
        << dangerousMoves
        << '\n';

    std::cout
        << "Decision               : "
        << decision
        << '\n';

    std::cout
        << "Selected move          : "
        << static_cast<int>(move.from)
        << " -> "
        << static_cast<int>(move.to)
        << '\n';

    std::cout
        << "===============================\n\n";

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
            "DefenseAI",
            []() -> std::unique_ptr<Agent>
            {
                return std::make_unique<DefenseAI>();
            });

        return true;
    }();
}