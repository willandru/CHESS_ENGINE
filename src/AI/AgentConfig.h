#pragma once

#include <memory>

#include "Agent.h"

class AgentConfig
{
public:

    enum class Player
    {
        Human,
        RandomAI,
        CaptureAI,
        DefenseAI,
        DefenseCaptureAI,
        CaptureDefenseAI,
        RLAgentAI
    };

    static void load();

    static std::unique_ptr<Agent> getPlayer1();
    static std::unique_ptr<Agent> getPlayer2();

private:

    static Player player1;
    static Player player2;
};