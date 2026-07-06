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
    // Information required to restore the position
    //------------------------------------------------

    MoveExecutor::Undo undo;

    //------------------------------------------------
    // Child nodes
    //------------------------------------------------

    std::vector<DecisionNode> children;

    //------------------------------------------------
    // Search information
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