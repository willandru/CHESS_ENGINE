#include "DecisionTreeEngine.h"

#include "MoveGenerator.h"
#include "MoveFilter.h"

//====================================================
// CONSTRUCTOR
//====================================================

DecisionTreeEngine::DecisionTreeEngine()
{
    clear();
}

//====================================================
// CLEAR
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

void DecisionTreeEngine::build(
    const GameState& state,
    uint32_t depth)
{
    clear();

    GameState copy = state;

    root.sideToMove = copy.getTurn();

    expand(copy, root, depth);
}

//====================================================
// EXPAND
//====================================================

void DecisionTreeEngine::expand(
    GameState& state,
    DecisionNode& node,
    uint32_t remainingDepth)
{
    ++visitedNodes;

    if (node.depth > maxDepth)
        maxDepth = node.depth;

    node.sideToMove = state.getTurn();

    node.inCheck =
        MoveFilter::isKingInCheck(
            state,
            state.getTurn());

    //------------------------------------------------
    // Stop by depth
    //------------------------------------------------

    if (remainingDepth == 0)
    {
        node.terminal = true;
        return;
    }

    //------------------------------------------------
    // Generate legal moves
    //------------------------------------------------

    std::vector<Move> moves;

    MoveGenerator::generateAllMoves(
        state,
        moves);

    MoveFilter::filterLegalMoves(
        state,
        moves);

    //------------------------------------------------
    // No legal moves
    //------------------------------------------------

    if (moves.empty())
    {
        node.terminal = true;

        node.checkmate =
            MoveFilter::isCheckmate(
                state,
                state.getTurn());

        node.stalemate =
            MoveFilter::isStalemate(
                state,
                state.getTurn());

        return;
    }

    //------------------------------------------------
    // Expand children
    //------------------------------------------------

    node.children.reserve(moves.size());

    for (const Move& move : moves)
    {
        node.children.emplace_back();

        DecisionNode& child =
            node.children.back();

        child.move = move;
        child.depth = node.depth + 1;

        //------------------------------------------------
        // Apply move
        //------------------------------------------------

        child.undo =
            MoveExecutor::execute(
                state,
                move);

        //------------------------------------------------
        // Recursive expansion
        //------------------------------------------------

        expand(
            state,
            child,
            remainingDepth - 1);

        //------------------------------------------------
        // Restore position
        //------------------------------------------------

        MoveExecutor::undo(
            state,
            move,
            child.undo);
    }
}

//====================================================
// ROOT
//====================================================

const DecisionNode&
DecisionTreeEngine::getRoot() const
{
    return root;
}

DecisionNode&
DecisionTreeEngine::getRoot()
{
    return root;
}

//====================================================
// STATISTICS
//====================================================

uint64_t
DecisionTreeEngine::getVisitedNodes() const
{
    return visitedNodes;
}

uint32_t
DecisionTreeEngine::getMaxDepth() const
{
    return maxDepth;
}