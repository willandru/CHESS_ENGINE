#pragma once

#include "Agent.h"
#include "DecisionTreeEngine.h"

class CaptureAI : public Agent
{
public:
    CaptureAI();

    bool isHuman() const override;

    bool decide(
        const GameState& state,
        Move& move
    ) override;

private:
    DecisionTreeEngine tree;
};