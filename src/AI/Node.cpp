#include "Node.h"

//====================================================
// CONSTRUCTORS
//====================================================

Node::Node()
    : from(0),
      to(0)
{
}

Node::Node(
    uint8_t from,
    uint8_t to)
    : from(from),
      to(to)
{
}

//====================================================
// ACCESS
//====================================================

uint8_t Node::getFrom() const
{
    return from;
}

uint8_t Node::getTo() const
{
    return to;
}

void Node::setFrom(uint8_t square)
{
    from = square;
}

void Node::setTo(uint8_t square)
{
    to = square;
}