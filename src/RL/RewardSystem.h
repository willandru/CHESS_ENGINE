#pragma once

#include <cstdint>

#include "DecisionNode.h"

class RewardSystem
{

public:

    //------------------------------------------------
    // Constructor
    //------------------------------------------------

    RewardSystem();



    //------------------------------------------------
    // Reset episode reward
    //------------------------------------------------

    void reset();



    //------------------------------------------------
    // Calculate reward
    //
    // node : resulting position
    // turn : current game turn
    //
    //------------------------------------------------

    float calculateReward(
        const DecisionNode& node,
        uint32_t turn);



    //------------------------------------------------
    // Current reward
    //------------------------------------------------

    float getCurrentReward() const;



private:

    //------------------------------------------------
    // Cached reward
    //------------------------------------------------

    float currentReward = 0.0f;



private:

    //------------------------------------------------
    // Reward limits
    //------------------------------------------------

    static constexpr float MAX_REWARD = 100.0f;

    static constexpr float MIN_REWARD = -100.0f;



    //------------------------------------------------
    // Living penalty
    //
    // Encourages shorter games.
    //------------------------------------------------

    static constexpr float TURN_PENALTY = 1.0f;



    //------------------------------------------------
    // Intermediate rewards
    //------------------------------------------------

    static constexpr float CHECK_BONUS = 5.0f;



    //------------------------------------------------
    // Terminal rewards
    //------------------------------------------------

    static constexpr float CHECKMATE_BONUS = 100.0f;

    static constexpr float LOSS_PENALTY = -100.0f;

    static constexpr float STALEMATE_PENALTY = -25.0f;

};