#pragma once

#include "GameState.h"
#include "Move.h"

class Agent
{
public:

    virtual ~Agent() = default;

    virtual bool decide(
        const GameState& state,
        Move& move) = 0;
};