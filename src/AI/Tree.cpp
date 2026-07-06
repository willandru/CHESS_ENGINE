#include "Tree.h"

//====================================================
// CONSTRUCTOR
//====================================================

Tree::Tree()
{
}

//====================================================
// STATE
//====================================================

void Tree::clear()
{
    nodes.clear();
    children.clear();
}

bool Tree::isEmpty() const
{
    return nodes.empty();
}

//====================================================
// NODES
//====================================================

uint32_t Tree::addNode(
    const Node& node)
{
    nodes.push_back(node);

    children.emplace_back();

    return static_cast<uint32_t>(
        nodes.size() - 1
    );
}

const Node& Tree::getNode(
    uint32_t index) const
{
    return nodes[index];
}

Node& Tree::getNode(
    uint32_t index)
{
    return nodes[index];
}

uint32_t Tree::getNodeCount() const
{
    return static_cast<uint32_t>(
        nodes.size()
    );
}

//====================================================
// RELATIONS
//====================================================

void Tree::addChild(
    uint32_t parent,
    uint32_t child)
{
    children[parent].push_back(child);
}

const std::vector<uint32_t>& Tree::getChildren(
    uint32_t parent) const
{
    return children[parent];
}