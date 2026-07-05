#pragma once

#include "Agent.h"

class RandomAI : public Agent
{
public:

    RandomAI();

    bool decide(
        const GameState& state,
        Move& move) override;
};