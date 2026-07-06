#pragma once

#include "Agent.h"
#include "DecisionTreeEngine.h"

class CaptureDefenseAI : public Agent
{
public:
    CaptureDefenseAI();

    bool isHuman() const override;

    bool decide(
        const GameState& state,
        Move& move) override;

private:
    DecisionTreeEngine tree;
};