#include "AgentConfig.h"

#include "AgentRegistry.h"

namespace
{
    constexpr const char* Human     = "Human";
    constexpr const char* RandomAI  = "RandomAI";
    constexpr const char* CaptureAI = "CaptureAI";

    const char* toString(AgentConfig::Player player)
    {
        switch (player)
        {
        case AgentConfig::Player::Human:
            return Human;

        case AgentConfig::Player::RandomAI:
            return RandomAI;

        case AgentConfig::Player::CaptureAI:
            return CaptureAI;
        }

        return Human;
    }
}

//====================================================
// STATIC MEMBERS
//====================================================

AgentConfig::Player AgentConfig::player1;
AgentConfig::Player AgentConfig::player2;

//====================================================

void AgentConfig::load()
{
    // Configuración actual de la partida

    player1 = Player::CaptureAI;
    player2 = Player::CaptureAI;
}

//====================================================

std::unique_ptr<Agent> AgentConfig::getPlayer1()
{
    return AgentRegistry::create(
        toString(player1)
    );
}

//====================================================

std::unique_ptr<Agent> AgentConfig::getPlayer2()
{
    return AgentRegistry::create(
        toString(player2)
    );
}