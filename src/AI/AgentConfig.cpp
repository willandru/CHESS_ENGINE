#include "AgentConfig.h"

#include "AgentRegistry.h"
#include <iostream>

std::string AgentConfig::player1Type = "RandomAI";
std::string AgentConfig::player2Type = "Human";

//====================================================

void AgentConfig::load()
{
    // 🔴 simulación de JSON
    player1Type = "RandomAI";
    player2Type = "Human";

    std::cout << "AgentConfig loaded (SIMULATED)\n";
    std::cout << "Player1 = " << player1Type << "\n";
    std::cout << "Player2 = " << player2Type << "\n";
}

//====================================================

std::unique_ptr<Agent> AgentConfig::getPlayer1()
{
    return AgentRegistry::create(player1Type);
}

//====================================================

std::unique_ptr<Agent> AgentConfig::getPlayer2()
{
    return AgentRegistry::create(player2Type);
}