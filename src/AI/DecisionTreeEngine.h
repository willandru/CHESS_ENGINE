#pragma once

#include <vector>
#include "Node.h"
#include "Move.h"

class DecisionTreeEngine
{
public:
    static void expandNode(
        const Node& parent,
        std::vector<Node>& outChildren
    );
};