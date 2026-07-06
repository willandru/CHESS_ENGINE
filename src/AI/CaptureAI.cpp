#include "CaptureAI.h"

#include "AgentRegistry.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

CaptureAI::CaptureAI()
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

bool CaptureAI::isHuman() const
{
    return false;
}

bool CaptureAI::decide(
    const GameState& state,
    Move& move)
{
    //------------------------------------------------
    // Search tree
    //
    // Depth 0 : current position
    // Depth 1 : our move
    // Depth 2 : opponent move
    // Depth 3 : our reply
    //------------------------------------------------

    tree.build(state, 3);

    const DecisionNode& root = tree.getRoot();

    if (root.children.empty())
        return false;

    //------------------------------------------------
    // Analysis
    //------------------------------------------------

    std::vector<int> immediateCaptures;
    std::vector<int> forcedCaptures;

    uint32_t analysedRootMoves = 0;
    uint32_t analysedEnemyReplies = 0;
    uint32_t analysedFutureMoves = 0;

    //------------------------------------------------
    // Analyse every legal move
    //------------------------------------------------

    for (size_t i = 0; i < root.children.size(); ++i)
    {
        ++analysedRootMoves;

        const DecisionNode& firstMove =
            root.children[i];

        //------------------------------------------------
        // Immediate capture
        //------------------------------------------------

        if (firstMove.move.isCapture())
        {
            immediateCaptures.push_back(
                static_cast<int>(i));
        }

        //------------------------------------------------
        // No opponent replies
        //------------------------------------------------

        if (firstMove.children.empty())
            continue;

        //------------------------------------------------
        // Verify whether EVERY opponent reply still
        // allows us to capture on our next move.
        //------------------------------------------------

        bool forced = true;

        for (const DecisionNode& enemyReply :
             firstMove.children)
        {
            ++analysedEnemyReplies;

            bool captureExists = false;

            for (const DecisionNode& ourReply :
                 enemyReply.children)
            {
                ++analysedFutureMoves;

                if (ourReply.move.isCapture())
                {
                    captureExists = true;
                    break;
                }
            }

            //--------------------------------------------
            // Opponent found a defence
            //--------------------------------------------

            if (!captureExists)
            {
                forced = false;
                break;
            }
        }

        if (forced)
        {
            forcedCaptures.push_back(
                static_cast<int>(i));
        }
    }

    //------------------------------------------------
    // Decision
    //------------------------------------------------

    const char* decision = "RANDOM";

    if (!immediateCaptures.empty())
    {
        int idx =
            immediateCaptures[
                std::rand() %
                immediateCaptures.size()
            ];

        move = root.children[idx].move;

        decision = "IMMEDIATE";
    }
    else if (!forcedCaptures.empty())
    {
        int idx =
            forcedCaptures[
                std::rand() %
                forcedCaptures.size()
            ];

        move = root.children[idx].move;

        decision = "FORCED";
    }
    else
    {
        int idx =
            std::rand() %
            static_cast<int>(
                root.children.size());

        move = root.children[idx].move;
    }

    //------------------------------------------------
    // Debug
    //------------------------------------------------

    std::cout << "\n========== CaptureAI ==========\n";

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
        << analysedRootMoves
        << '\n';

    std::cout
        << "Immediate captures     : "
        << immediateCaptures.size()
        << '\n';

    std::cout
        << "Forced capture moves   : "
        << forcedCaptures.size()
        << '\n';

    std::cout
        << "Enemy replies analysed : "
        << analysedEnemyReplies
        << '\n';

    std::cout
        << "Future moves analysed  : "
        << analysedFutureMoves
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
            "CaptureAI",
            []() -> std::unique_ptr<Agent>
            {
                return std::make_unique<CaptureAI>();
            });

        return true;
    }();
}