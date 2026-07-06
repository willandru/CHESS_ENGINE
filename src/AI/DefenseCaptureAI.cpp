#include "DefenseCaptureAI.h"
#include "AgentRegistry.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

DefenseCaptureAI::DefenseCaptureAI()
{
    static bool seeded = false;
    if (!seeded)
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }
}

bool DefenseCaptureAI::isHuman() const
{
    return false;
}

bool DefenseCaptureAI::decide(
    const GameState& state,
    Move& move)
{
    tree.build(state, 3);

    const DecisionNode& root = tree.getRoot();
    if (root.children.empty())
        return false;

    std::vector<int> safeMoves;
    std::vector<int> immediateCaptures;
    std::vector<int> futureCaptures;

    uint32_t enemyReplies = 0;
    uint32_t futureChecks = 0;
    uint32_t dangerous = 0;

    std::cout << "\n===== DefenseCaptureAI (CLEAN TRACE) =====\n";
    std::cout << "Root moves: " << root.children.size() << "\n\n";

    // =========================================================
    // PHASE 1: SAFETY CHECK (DEPTH 2)
    // =========================================================
    std::cout << "--- PHASE 1: SAFETY (DEPTH 2) ---\n";

    for (size_t i = 0; i < root.children.size(); ++i)
    {
        const DecisionNode& node = root.children[i];

        bool safe = true;

        std::cout << "[MOVE " << i << "] "
                  << (int)node.move.from << " -> " << (int)node.move.to;

        if (node.children.empty())
        {
            std::cout << " | no replies -> SAFE\n";
            safeMoves.push_back((int)i);
            continue;
        }

        std::cout << " | replies=" << node.children.size();

        for (const DecisionNode& reply : node.children)
        {
            ++enemyReplies;
            if (reply.move.isCapture())
                safe = false;
        }

        if (safe)
        {
            std::cout << " | SAFE\n";
            safeMoves.push_back((int)i);
        }
        else
        {
            std::cout << " | UNSAFE\n";
            ++dangerous;
        }
    }

    // =========================================================
    // PHASE 2: TACTICAL LOOKAHEAD (DEPTH 3)
    // ONLY ON SAFE MOVES
    // =========================================================
    std::cout << "\n--- PHASE 2: TACTICAL (DEPTH 3) ---\n";

    for (int idx : safeMoves)
    {
        const DecisionNode& node = root.children[idx];

        bool immediate = node.move.isCapture();
        bool future = false;

        std::cout << "[SAFE MOVE] "
                  << (int)node.move.from << " -> " << (int)node.move.to;

        if (immediate)
        {
            std::cout << " | IMMEDIATE CAPTURE";
            immediateCaptures.push_back(idx);
        }

        for (const DecisionNode& reply : node.children)
        {
            for (const DecisionNode& reply2 : reply.children)
            {
                ++futureChecks;

                if (reply2.move.isCapture())
                {
                    future = true;
                }
            }
        }

        if (future)
        {
            std::cout << " | FUTURE CAPTURE PATH";
            futureCaptures.push_back(idx);
        }

        std::cout << "\n";
    }

    // =========================================================
    // PHASE 3: DECISION
    // =========================================================
    const char* decision = "RANDOM";

    if (!immediateCaptures.empty())
    {
        int idx = immediateCaptures[std::rand() % immediateCaptures.size()];
        move = root.children[idx].move;
        decision = "IMMEDIATE_CAPTURE";
    }
    else if (!futureCaptures.empty())
    {
        int idx = futureCaptures[std::rand() % futureCaptures.size()];
        move = root.children[idx].move;
        decision = "FUTURE_CAPTURE";
    }
    else if (!safeMoves.empty())
    {
        int idx = safeMoves[std::rand() % safeMoves.size()];
        move = root.children[idx].move;
        decision = "SAFE_MOVE";
    }
    else
    {
        int idx = std::rand() % (int)root.children.size();
        move = root.children[idx].move;
    }

    // =========================================================
    // SUMMARY (CLEAN)
    // =========================================================
    std::cout << "\n===== SUMMARY =====\n";
    std::cout << "Visited nodes      : " << tree.getVisitedNodes() << "\n";
    std::cout << "Tree depth         : " << tree.getMaxDepth() << "\n";
    std::cout << "Safe moves         : " << safeMoves.size() << "\n";
    std::cout << "Immediate captures : " << immediateCaptures.size() << "\n";
    std::cout << "Future captures    : " << futureCaptures.size() << "\n";
    std::cout << "Enemy replies      : " << enemyReplies << "\n";
    std::cout << "Future checks      : " << futureChecks << "\n";
    std::cout << "Dangerous moves    : " << dangerous << "\n";
    std::cout << "Decision           : " << decision << "\n";
    std::cout << "Selected move      : "
              << (int)move.from << " -> " << (int)move.to << "\n";
    std::cout << "====================\n\n";

    return true;
}

namespace
{
    const bool registered = []()
    {
        AgentRegistry::registerAgent(
            "DefenseCaptureAI",
            []() -> std::unique_ptr<Agent>
            {
                return std::make_unique<DefenseCaptureAI>();
            });

        return true;
    }();
}