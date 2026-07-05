#include "DecisionTreeEngine.h"

#include "MoveGenerator.h"
#include "MoveFilter.h"

DecisionTreeEngine::DecisionTreeEngine()
{
    clear();
}

//====================================================
// CLEAR (SOLO UNA VEZ)
//====================================================
void DecisionTreeEngine::clear()
{
    root = DecisionNode{};
    visitedNodes = 0;
    maxDepth = 0;
}

//====================================================
// BUILD
//====================================================
void DecisionTreeEngine::build(const GameState& state, uint32_t depth)
{
    clear();

    GameState copy = state;
    expand(copy, root, depth);
}

//====================================================
// EXPAND (CORE ENGINE)
//====================================================
void DecisionTreeEngine::expand(
    GameState& state,
    DecisionNode& node,
    uint32_t depth)
{
    ++visitedNodes;

    if (node.depth > maxDepth)
        maxDepth = node.depth;

    if (depth == 0)
    {
        node.terminal = true;
        return;
    }

    std::vector<Move> moves;
    MoveGenerator::generateAllMoves(state, moves);
    MoveFilter::filterLegalMoves(state, moves);

    node.children.reserve(moves.size());

    for (const Move& move : moves)
    {
        node.children.emplace_back();
        DecisionNode& child = node.children.back();

        child.move = move;
        child.depth = node.depth + 1;

        // APPLY MOVE
        child.undo = MoveExecutor::execute(state, move);

        // RECURSION
        expand(state, child, depth - 1);

        // UNDO
        MoveExecutor::undo(state, move, child.undo);
    }
}

//====================================================
// ROOT ACCESS
//====================================================
const DecisionNode& DecisionTreeEngine::getRoot() const
{
    return root;
}

DecisionNode& DecisionTreeEngine::getRoot()
{
    return root;
}

//====================================================
// STATS
//====================================================
uint64_t DecisionTreeEngine::getVisitedNodes() const
{
    return visitedNodes;
}

uint32_t DecisionTreeEngine::getMaxDepth() const
{
    return maxDepth;
}