#pragma once

#include "GameState.h"
#include "Move.h"

//====================================================
// Agent (interfaz de decisión)
//====================================================
//
// Un agente SOLO decide movimientos.
// No modifica estado.
// No ejecuta.
//====================================================

class Agent
{
public:
    virtual ~Agent() = default;

    virtual Move decide(const GameState& state) = 0;
};