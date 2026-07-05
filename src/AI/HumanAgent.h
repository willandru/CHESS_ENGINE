#pragma once

#include "Agent.h"

class HumanAgent : public Agent
{
public:
    HumanAgent();

    bool isHuman() const override;

    void onSquareClicked(uint8_t square) override;

    bool decide(
        const GameState& state,
        Move& move
    ) override;

private:
    enum class ClickState
    {
        WaitingSource,
        WaitingTarget
    };

    ClickState clickState;

    uint8_t sourceSquare;

    bool hasMove;
    Move pendingMove;
};