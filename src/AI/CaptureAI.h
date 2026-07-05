#pragma once

#include "Agent.h"

class CaptureAI : public Agent
{
public:

    CaptureAI();

    //------------------------------------------------
    // AGENT
    //------------------------------------------------

    bool isHuman() const override;

    bool decide(
        const GameState& state,
        Move& move
    ) override;
};