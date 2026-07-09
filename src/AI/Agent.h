#pragma once

#include <cstdint>

#include "GameState.h"
#include "Move.h"

class Agent
{
public:

    virtual ~Agent() = default;

    //------------------------------------------------
    // TYPE
    //------------------------------------------------

    virtual bool isHuman() const = 0;

    //------------------------------------------------
    // INPUT
    //------------------------------------------------

    virtual void onSquareClicked(uint8_t square)
    {
        (void)square;
    }

    //------------------------------------------------
    // DECISION
    //------------------------------------------------
    // Devuelve true cuando el agente tiene un movimiento
    // listo para ejecutar.
    //
    // IA:
    //   - decide inmediatamente.
    //
    // Humano:
    //   - devuelve false hasta completar la selección
    //     origen → destino mediante clics.
    //------------------------------------------------

    virtual bool decide(
        const GameState& state,
        Move& move
    ) = 0;

    virtual void observe(
    const GameState& state)
    {
    }
};