#pragma once

#include "Agent.h"

#include <memory>
#include <string>


class RLSystem;



//====================================================
// RL AGENT AI
//
// Interface between chess engine and RLSystem.
//
// Responsible for:
// - Requesting actions
// - Sending environment updates
// - Ending episodes
// - Model persistence
//
//====================================================

class RLAgentAI : public Agent
{

public:


    //================================================
    // Constructor
    //================================================

    RLAgentAI();



    //================================================
    // Agent interface
    //================================================

    bool isHuman() const override;



    bool decide(
        const GameState& state,
        Move& move
    ) override;



    //================================================
    // RL environment callbacks
    //
    // Called by game engine after:
    //
    // Move execution
    //
    //================================================

    void observe(
        const GameState& state);



    //================================================
    // Episode termination
    //
    // victory:
    //
    // true  -> RL agent won
    // false -> RL agent lost
    //
    //================================================

    void finishGame(
        bool victory);



    //================================================
    // Model persistence
    //================================================

    bool saveModel(
        const std::string& filename);



    bool loadModel(
        const std::string& filename);



private:


    //================================================
    // Reinforcement Learning controller
    //================================================

    std::unique_ptr<RLSystem> rlSystem;

};