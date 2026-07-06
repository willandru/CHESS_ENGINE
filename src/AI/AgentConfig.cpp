#include "AgentConfig.h"

#include "AgentRegistry.h"

namespace
{
    constexpr const char* Human     = "Human";
    constexpr const char* RandomAI  = "RandomAI";
    constexpr const char* CaptureAI = "CaptureAI";
    constexpr const char* DefenseAI = "DefenseAI";
    constexpr const char* DefenseCaptureAI = "DefenseCaptureAI";
    constexpr const char* CaptureDefenseAI = "CaptureDefenseAI";

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
        
        case AgentConfig::Player::DefenseAI:
            return DefenseAI;

        case AgentConfig::Player::DefenseCaptureAI:
            return DefenseCaptureAI;
        
        case AgentConfig::Player::CaptureDefenseAI:
            return CaptureDefenseAI;
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

    player1 = Player::Human;
    player2 = Player::Human;
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