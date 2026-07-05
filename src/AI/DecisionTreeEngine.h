#pragma once

#include <cstdint>
#include <vector>

#include "GameState.h"
#include "Move.h"
#include "MoveExecutor.h"

struct DecisionNode
{
    Move move;
    MoveExecutor::Undo undo;

    std::vector<DecisionNode> children;

    int depth = 0;
    float evaluation = 0.0f;
    bool terminal = false;
};

class DecisionTreeEngine
{
public:
    DecisionTreeEngine();

    void build(const GameState& state, uint32_t depth);
    void clear();

    const DecisionNode& getRoot() const;
    DecisionNode& getRoot();

    uint64_t getVisitedNodes() const;
    uint32_t getMaxDepth() const;

private:
    void expand(GameState& state, DecisionNode& node, uint32_t depth);

private:
    DecisionNode root;

    uint64_t visitedNodes = 0;
    uint32_t maxDepth = 0;
};