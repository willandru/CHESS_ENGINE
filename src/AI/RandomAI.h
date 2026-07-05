#pragma once

#include "Agent.h"

class RandomAI : public Agent
{
public:

    RandomAI();

    //------------------------------------------------
    // AGENT
    //------------------------------------------------

    bool isHuman() const override;

    bool decide(
        const GameState& state,
        Move& move
    ) override;
};