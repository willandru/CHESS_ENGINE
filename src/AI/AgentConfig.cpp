#include "AgentConfig.h"

#include "AgentRegistry.h"
#include "RLAgentAI.h"



namespace
{

    constexpr const char* Human_Name =
        "Human";


    constexpr const char* RandomAI_Name =
        "RandomAI";


    constexpr const char* CaptureAI_Name =
        "CaptureAI";


    constexpr const char* DefenseAI_Name =
        "DefenseAI";


    constexpr const char* DefenseCaptureAI_Name =
        "DefenseCaptureAI";


    constexpr const char* CaptureDefenseAI_Name =
        "CaptureDefenseAI";


    constexpr const char* RLAgentAI_Name =
        "RLAgentAI";



    const char* toString(
        AgentConfig::Player player)
    {

        switch(player)
        {

        case AgentConfig::Player::Human:
            return Human_Name;


        case AgentConfig::Player::RandomAI:
            return RandomAI_Name;


        case AgentConfig::Player::CaptureAI:
            return CaptureAI_Name;


        case AgentConfig::Player::DefenseAI:
            return DefenseAI_Name;


        case AgentConfig::Player::DefenseCaptureAI:
            return DefenseCaptureAI_Name;


        case AgentConfig::Player::CaptureDefenseAI:
            return CaptureDefenseAI_Name;


        case AgentConfig::Player::RLAgentAI:
            return RLAgentAI_Name;

        }


        return Human_Name;
    }

}



//====================================================
// STATIC MEMBERS
//====================================================

AgentConfig::Player AgentConfig::player1 =
    AgentConfig::Player::Human;


AgentConfig::Player AgentConfig::player2 =
    AgentConfig::Player::Human;



//====================================================
// LOAD
//====================================================

void AgentConfig::load()
{

    //------------------------------------------------
    // CURRENT MATCH
    //------------------------------------------------

    player1 =
        Player::Human;


    player2 =
        Player::RLAgentAI;

}



//====================================================
// MODEL PATHS
//====================================================

const char* AgentConfig::getPlayer1ModelPath()
{
    return "../src/RL/models/player1.model";
}

const char* AgentConfig::getPlayer2ModelPath()
{
    return "../src/RL/models/player2.model";
}


//====================================================
// PLAYER 1
//====================================================

std::unique_ptr<Agent> AgentConfig::getPlayer1()
{

    //------------------------------------------------
    // RL SPECIAL CASE
    //------------------------------------------------

    if(player1 == Player::RLAgentAI)
    {

        return std::make_unique<RLAgentAI>(
            getPlayer1ModelPath()
        );

    }



    //------------------------------------------------
    // NORMAL AGENTS
    //------------------------------------------------

    return AgentRegistry::create(
        toString(player1)
    );

}



//====================================================
// PLAYER 2
//====================================================

std::unique_ptr<Agent> AgentConfig::getPlayer2()
{

    //------------------------------------------------
    // RL SPECIAL CASE
    //------------------------------------------------

    if(player2 == Player::RLAgentAI)
    {

        return std::make_unique<RLAgentAI>(
            getPlayer2ModelPath()
        );

    }



    //------------------------------------------------
    // NORMAL AGENTS
    //------------------------------------------------

    return AgentRegistry::create(
        toString(player2)
    );

}