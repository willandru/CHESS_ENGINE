#pragma once

#include <memory>
#include <string>

#include "Agent.h"

class AgentConfig
{
public:
    static void load(); // simulación (luego JSON real)

    static std::unique_ptr<Agent> getPlayer1();
    static std::unique_ptr<Agent> getPlayer2();

private:
    static std::string player1Type;
    static std::string player2Type;
};