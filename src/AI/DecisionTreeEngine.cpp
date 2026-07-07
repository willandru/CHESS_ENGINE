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
// BUILD FROM ONE PIECE
//====================================================

void DecisionTreeEngine::build(
    const GameState& state,
    uint8_t sourceSquare,
    uint32_t depth)
{
    clear();

    GameState copy = state;

    root.sideToMove = copy.getTurn();

    //------------------------------------------------
    // Depth zero
    //------------------------------------------------

    if (depth == 0)
    {
        root.terminal = true;
        return;
    }

    //------------------------------------------------
    // Generate only selected piece moves
    //------------------------------------------------

    std::vector<Move> moves;

    MoveGenerator::generatePieceMoves(
        copy,
        sourceSquare,
        moves);

    MoveFilter::filterLegalMoves(
        copy,
        moves);

    //------------------------------------------------
    // No legal moves
    //------------------------------------------------

    if (moves.empty())
    {
        root.terminal = true;
        return;
    }

    //------------------------------------------------
    // Expand first level
    //------------------------------------------------

    root.children.reserve(moves.size());

    for (const Move& move : moves)
    {
        root.children.emplace_back();

        DecisionNode& child =
            root.children.back();

        child.move = move;
        child.depth = 1;

        child.undo =
            MoveExecutor::execute(
                copy,
                move);

        expand(
            copy,
            child,
            depth - 1);

        MoveExecutor::undo(
            copy,
            move,
            child.undo);
    }
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

    //------------------------------------------------
    // POSITION INFORMATION
    //------------------------------------------------

    node.sideToMove = state.getTurn();

    node.inCheck =
        MoveFilter::isKingInCheck(
            state,
            state.getTurn());

    node.checkmate =
        MoveFilter::isCheckmate(
            state,
            state.getTurn());

    node.stalemate =
        MoveFilter::isStalemate(
            state,
            state.getTurn());

    //------------------------------------------------
    // TERMINAL POSITION
    //------------------------------------------------

    if (node.checkmate || node.stalemate)
    {
        node.terminal = true;
        return;
    }

    //------------------------------------------------
    // STOP BY DEPTH
    //------------------------------------------------

    if (remainingDepth == 0)
    {
        node.terminal = true;
        return;
    }

    //------------------------------------------------
    // GENERATE LEGAL MOVES
    //------------------------------------------------

    std::vector<Move> moves;

    MoveGenerator::generateAllMoves(
        state,
        moves);

    MoveFilter::filterLegalMoves(
        state,
        moves);

    //------------------------------------------------
    // EXPAND CHILDREN
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
        // APPLY MOVE
        //------------------------------------------------

        child.undo =
            MoveExecutor::execute(
                state,
                move);

        //------------------------------------------------
        // RECURSIVE EXPANSION
        //------------------------------------------------

        expand(
            state,
            child,
            remainingDepth - 1);

        //------------------------------------------------
        // RESTORE POSITION
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