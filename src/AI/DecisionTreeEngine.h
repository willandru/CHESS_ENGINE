#pragma once

#include <vector>
#include <cstdint>

#include "Node.h"
#include "MoveGenerator.h"
#include "MoveFilter.h"
#include "MoveExecutor.h"

class DecisionTreeEngine
{
public:

    void reset(const GameState& rootState);

    uint32_t expand(uint32_t nodeIndex, std::vector<uint32_t>& outChildren);

    Node& getNode(uint32_t index);
    const Node& getRoot() const;

    void clear();

private:

    std::vector<Node> nodes;
    uint32_t rootIndex = 0;
};