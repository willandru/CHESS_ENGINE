#pragma once

#include "Agent.h"
#include "DecisionTreeEngine.h"

class DefenseCaptureAI : public Agent
{
public:

    DefenseCaptureAI();

    bool isHuman() const override;

    bool decide(
        const GameState& state,
        Move& move) override;

private:

    DecisionTreeEngine tree;
};