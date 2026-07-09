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


    //------------------------------------------------
    // CONFIGURATION
    //------------------------------------------------

    static void load();



    //------------------------------------------------
    // CREATE PLAYERS
    //------------------------------------------------

    static std::unique_ptr<Agent> getPlayer1();

    static std::unique_ptr<Agent> getPlayer2();



    //------------------------------------------------
    // RL MODEL PATHS
    //------------------------------------------------

    static const char* getPlayer1ModelPath();

    static const char* getPlayer2ModelPath();



private:

    static Player player1;

    static Player player2;

};