#pragma once

#include "Agent.h"
#include "DecisionTreeEngine.h"

class DefenseAI : public Agent
{
public:

    DefenseAI();

    //------------------------------------------------
    // Agent
    //------------------------------------------------

    bool isHuman() const override;

    bool decide(
        const GameState& state,
        Move& move
    ) override;

private:

    DecisionTreeEngine tree;
};