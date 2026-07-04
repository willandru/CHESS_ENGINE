#pragma once

#include <cstdint>
#include "GameState.h"
#include "Move.h"

struct Node
{
    GameState state;

    uint32_t parent;   // índice del nodo padre
    uint32_t depth;    // profundidad en el árbol

    Move move;         // movimiento que generó este nodo

    float score;       // evaluación externa (IA la llena)

    Node()
        : parent(0),
          depth(0),
          score(0.0f)
    {}
};