#pragma once

#include <cstdint>

class RewardSystem
{

public:

    //------------------------------------------------
    // Constructor
    //------------------------------------------------

    RewardSystem();



    //------------------------------------------------
    // Reset episode
    //------------------------------------------------

    void reset();



    //------------------------------------------------
    // Calculate reward
    //
    // turn       : current ply / move number
    // checkmate  : agent wins
    // lost       : agent loses
    // stalemate  : draw
    //
    //------------------------------------------------

    float calculateReward(
        uint32_t turn,
        bool checkmate,
        bool lost,
        bool stalemate);



    //------------------------------------------------
    // Last computed reward
    //------------------------------------------------

    float getCurrentReward() const;



private:

    //------------------------------------------------
    // Cached reward
    //------------------------------------------------

    float currentReward = 0.0f;



private:

    //------------------------------------------------
    // Reward configuration
    //------------------------------------------------

    static constexpr float MAX_REWARD = 100.0f;

    static constexpr float MIN_REWARD = -100.0f;

    //------------------------------------------------
    // Penalize long games
    //------------------------------------------------

    static constexpr float TURN_PENALTY = 1.0f;

    //------------------------------------------------
    // Terminal rewards
    //------------------------------------------------

    static constexpr float CHECKMATE_BONUS = 100.0f;

    static constexpr float LOSS_PENALTY = -100.0f;

    static constexpr float STALEMATE_PENALTY = -20.0f;

};