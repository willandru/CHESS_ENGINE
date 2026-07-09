#pragma once


#include "Agent.h"

#include <memory>
#include <string>


class RLSystem;



//====================================================
// RL AGENT AI
//
// Reinforcement Learning agent.
//
// Responsibilities:
//
// - Interface between ChessGame and RLSystem
// - Owns model path
// - Controls model loading/saving
//
//====================================================

class RLAgentAI : public Agent
{

public:


    //------------------------------------------------
    // Constructors
    //------------------------------------------------

    RLAgentAI();

    explicit RLAgentAI(
        const char* path);



    //------------------------------------------------
    // AGENT INTERFACE
    //------------------------------------------------

    bool isHuman() const override;



    bool decide(
        const GameState& state,
        Move& move
    ) override;



    void observe(
        const GameState& state
    ) override;



    //------------------------------------------------
    // RL EPISODE CONTROL
    //------------------------------------------------

    void finishGame(
        bool win);



    //------------------------------------------------
    // MODEL PATH
    //------------------------------------------------

    void setModelPath(
        const std::string& path);



    const std::string& getModelPath() const;



private:


    //------------------------------------------------
    // RL CORE SYSTEM
    //------------------------------------------------

    std::unique_ptr<RLSystem> rlSystem;



    //------------------------------------------------
    // Individual model file
    //
    // Example:
    //
    // player1 -> src/RL/models/player1.model
    // player2 -> src/RL/models/player2.model
    //
    //------------------------------------------------

    std::string modelPath;

};