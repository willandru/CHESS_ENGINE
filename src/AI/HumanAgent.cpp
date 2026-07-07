#include "HumanAgent.h"
#include "AgentRegistry.h"

#include <iostream>

//====================================================
// CONSTRUCTOR
//====================================================

HumanAgent::HumanAgent()
{
    clickState = ClickState::WaitingSource;
    sourceSquare = 0;
    hasMove = false;
}

//====================================================
// AGENT
//====================================================

bool HumanAgent::isHuman() const
{
    return true;
}

void HumanAgent::onSquareClicked(uint8_t square)
{
    if (clickState == ClickState::WaitingSource)
    {
        sourceSquare = square;
        clickState = ClickState::WaitingTarget;
        return;
    }

    pendingMove.from = sourceSquare;
    pendingMove.to = square;

    hasMove = true;
    clickState = ClickState::WaitingSource;
}

bool HumanAgent::decide(
    const GameState& state,
    Move& move)
{
    if (!hasMove)
        return false;

    move = pendingMove;
    hasMove = false;

    std::cout
        << "Human: "
        << GameState::squareToNotation(move.from)
        << " -> "
        << GameState::squareToNotation(move.to)
        << '\n';

    return true;
}

//====================================================
// REGISTRY
//====================================================

namespace
{
    bool registered = []()
    {
        AgentRegistry::registerAgent(
            "Human",
            []() -> std::unique_ptr<Agent>
            {
                return std::make_unique<HumanAgent>();
            });

        return true;
    }();
}