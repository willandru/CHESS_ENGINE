#pragma once

#include <vector>
#include "Move.h"
#include "MoveExecutor.h"

struct DecisionNode
{
    // Movimiento que llevó a este nodo desde su padre
    Move move;

    // Undo mínimo del movimiento aplicado
    MoveExecutor::Undo undo;

    // Árbol
    std::vector<DecisionNode> children;

    // Estructura
    int depth = 0;

    // Evaluación estática o de minimax
    float evaluation = 0.0f;

    // Flags opcionales (útiles en engines reales)
    bool terminal = false;   // checkmate / draw / leaf
};