#include "RewardSystem.h"

#include <algorithm>



//====================================================
// CONSTRUCTOR
//====================================================

RewardSystem::RewardSystem()
{
    reset();
}



//====================================================
// RESET
//====================================================

void RewardSystem::reset()
{
    currentReward = 0.0f;
}


//====================================================
// CALCULATE REWARD
//====================================================

float RewardSystem::calculateReward(
    const DecisionNode& node,
    uint32_t turn)
{

    //------------------------------------------------
    // Neutral reward
    //------------------------------------------------

    float reward = 0.0f;



    //------------------------------------------------
    // Penalize long games
    //
    // Faster victories receive higher reward.
    //------------------------------------------------

    reward -=
        static_cast<float>(turn) *
        TURN_PENALTY;



    //------------------------------------------------
    // Intermediate reward
    //
    // Encourage attacking positions.
    //------------------------------------------------

    if(node.inCheck)
    {
        reward += CHECK_BONUS;
    }



    //------------------------------------------------
    // Terminal game results
    //------------------------------------------------

    if(node.checkmate)
    {
        //------------------------------------------------
        // Winning state
        //------------------------------------------------

        reward += CHECKMATE_BONUS;
    }
    else if(node.stalemate)
    {
        //------------------------------------------------
        // Draw
        //------------------------------------------------

        reward += STALEMATE_PENALTY;
    }



    //------------------------------------------------
    // IMPORTANT:
    //
    // node.terminal does NOT mean losing.
    //
    // DecisionTreeEngine also marks nodes terminal
    // when search depth finishes.
    //
    // Therefore we do NOT apply LOSS_PENALTY here.
    //
    //------------------------------------------------



    //------------------------------------------------
    // Clamp reward
    //------------------------------------------------

    reward =
        std::clamp(
            reward,
            MIN_REWARD,
            MAX_REWARD);



    //------------------------------------------------
    // Store reward
    //------------------------------------------------

    currentReward = reward;


    return currentReward;
}



//====================================================
// GET CURRENT REWARD
//====================================================

float RewardSystem::getCurrentReward() const
{
    return currentReward;
}