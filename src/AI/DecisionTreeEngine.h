#pragma once

#include <cstdint>
#include <vector>

#include "GameState.h"
#include "Move.h"
#include "MoveExecutor.h"

struct DecisionNode
{
    //------------------------------------------------
    // Move that generated this node
    //------------------------------------------------

    Move move;

    //------------------------------------------------
    // Undo information
    //------------------------------------------------

    MoveExecutor::Undo undo;

    //------------------------------------------------
    // Tree
    //------------------------------------------------

    std::vector<DecisionNode> children;

    //------------------------------------------------
    // Node information
    //------------------------------------------------

    uint32_t depth = 0;

    float evaluation = 0.0f;

    //------------------------------------------------
    // Position information
    //------------------------------------------------

    PlayerSide sideToMove = PlayerSide::White;

    bool terminal = false;

    bool inCheck = false;

    bool checkmate = false;

    bool stalemate = false;
};

class DecisionTreeEngine
{
public:

    DecisionTreeEngine();

    //------------------------------------------------
    // Tree
    //------------------------------------------------

    void build(
        const GameState& state,
        uint32_t depth);

    void clear();

    //------------------------------------------------
    // Root access
    //------------------------------------------------

    const DecisionNode& getRoot() const;

    DecisionNode& getRoot();

    //------------------------------------------------
    // Statistics
    //------------------------------------------------

    uint64_t getVisitedNodes() const;

    uint32_t getMaxDepth() const;

private:

    void expand(
        GameState& state,
        DecisionNode& node,
        uint32_t remainingDepth);

private:

    DecisionNode root;

    uint64_t visitedNodes = 0;

    uint32_t maxDepth = 0;
};