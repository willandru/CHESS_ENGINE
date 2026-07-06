#pragma once

#include <cstdint>
#include <vector>

#include "Node.h"

class Tree
{
public:

    Tree();

    //------------------------------------------------
    // STATE
    //------------------------------------------------

    void clear();

    bool isEmpty() const;

    //------------------------------------------------
    // NODES
    //------------------------------------------------

    uint32_t addNode(const Node& node);

    const Node& getNode(uint32_t index) const;

    Node& getNode(uint32_t index);

    uint32_t getNodeCount() const;

    //------------------------------------------------
    // RELATIONS
    //------------------------------------------------

    void addChild(
        uint32_t parent,
        uint32_t child
    );

    const std::vector<uint32_t>& getChildren(
        uint32_t parent
    ) const;

private:

    std::vector<Node> nodes;

    std::vector<std::vector<uint32_t>> children;
};