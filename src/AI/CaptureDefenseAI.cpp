#include "CaptureDefenseAI.h"
#include "AgentRegistry.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

CaptureDefenseAI::CaptureDefenseAI()
{
    static bool seeded = false;
    if (!seeded)
    {
        std::srand((unsigned)std::time(nullptr));
        seeded = true;
    }
}

bool CaptureDefenseAI::isHuman() const
{
    return false;
}

bool CaptureDefenseAI::decide(
    const GameState& state,
    Move& move)
{
    tree.build(state, 3);

    const DecisionNode& root = tree.getRoot();
    if (root.children.empty())
        return false;

    std::vector<int> immediateAttacks;
    std::vector<int> futureAttacks;
    std::vector<int> defensiveMoves;

    uint32_t enemyReplies = 0;
    uint32_t futureChecks = 0;

    std::cout << "\n===== CaptureDefenseAI (STABLE TRACE) =====\n";
    std::cout << "Root moves: " << root.children.size() << "\n";

    // =========================================================
    // PHASE 1: IMMEDIATE ATTACK (DEPTH 1 ONLY)
    // =========================================================
    for (size_t i = 0; i < root.children.size(); ++i)
    {
        const DecisionNode& node = root.children[i];

        if (node.move.isCapture())
        {
            immediateAttacks.push_back((int)i);
        }
    }

    std::cout << "Immediate attacks: " << immediateAttacks.size() << "\n";

    // =========================================================
    // PHASE 2: FUTURE ATTACK (DEPTH 3 STRICT)
    // =========================================================
    for (size_t i = 0; i < root.children.size(); ++i)
    {
        const DecisionNode& node = root.children[i];

        if (node.children.empty())
            continue;

        bool attackLine = false;

        for (const DecisionNode& enemy : node.children)
        {
            ++enemyReplies;

            if (enemy.children.empty())
                continue;

            for (const DecisionNode& reply : enemy.children)
            {
                ++futureChecks;

                if (reply.move.isCapture())
                {
                    attackLine = true;
                    break;
                }
            }

            if (attackLine)
                break;
        }

        if (attackLine)
            futureAttacks.push_back((int)i);
    }

    std::cout << "Future attacks: " << futureAttacks.size() << "\n";

    // =========================================================
    // PHASE 3: DEFENSE (ONLY IF NOTHING ELSE)
    // =========================================================
    for (size_t i = 0; i < root.children.size(); ++i)
    {
        const DecisionNode& node = root.children[i];

        bool safe = true;

        if (node.children.empty())
        {
            defensiveMoves.push_back((int)i);
            continue;
        }

        for (const DecisionNode& enemy : node.children)
        {
            if (enemy.move.isCapture())
            {
                safe = false;
                break;
            }
        }

        if (safe)
            defensiveMoves.push_back((int)i);
    }

    std::cout << "Defense moves: " << defensiveMoves.size() << "\n";

    // =========================================================
    // DECISION PRIORITY
    // =========================================================
    const char* decision = "RANDOM";

    if (!immediateAttacks.empty())
    {
        int idx = immediateAttacks[std::rand() % immediateAttacks.size()];
        move = root.children[idx].move;
        decision = "IMMEDIATE_ATTACK";
    }
    else if (!futureAttacks.empty())
    {
        int idx = futureAttacks[std::rand() % futureAttacks.size()];
        move = root.children[idx].move;
        decision = "FUTURE_ATTACK";
    }
    else if (!defensiveMoves.empty())
    {
        int idx = defensiveMoves[std::rand() % defensiveMoves.size()];
        move = root.children[idx].move;
        decision = "DEFENSE";
    }
    else
    {
        int idx = std::rand() % (int)root.children.size();
        move = root.children[idx].move;
    }

    // =========================================================
    // SUMMARY (NO GARBAGE OUTPUT)
    // =========================================================
    std::cout << "\n===== SUMMARY =====\n";
    std::cout << "Visited nodes   : " << tree.getVisitedNodes() << "\n";
    std::cout << "Tree depth      : " << tree.getMaxDepth() << "\n";

    std::cout << "Enemy replies   : " << enemyReplies << "\n";
    std::cout << "Future checks   : " << futureChecks << "\n";

    std::cout << "Decision        : " << decision << "\n";
    std::cout << "Move            : "
              << (int)move.from << " -> " << (int)move.to << "\n";

    std::cout << "===================\n\n";

    return true;
}

namespace
{
    const bool registered = []()
    {
        AgentRegistry::registerAgent(
            "CaptureDefenseAI",
            []() -> std::unique_ptr<Agent>
            {
                return std::make_unique<CaptureDefenseAI>();
            });

        return true;
    }();
}