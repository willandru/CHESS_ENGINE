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
    uint32_t turn,
    bool checkmate,
    bool lost,
    bool stalemate)
{

    //------------------------------------------------
    // Start with neutral reward
    //------------------------------------------------

    float reward = 0.0f;



    //------------------------------------------------
    // Encourage faster victories
    //------------------------------------------------

    reward -=
        static_cast<float>(turn) *
        TURN_PENALTY;



    //------------------------------------------------
    // Terminal states
    //------------------------------------------------

    if(checkmate)
    {
        reward += CHECKMATE_BONUS;
    }

    if(lost)
    {
        reward += LOSS_PENALTY;
    }

    if(stalemate)
    {
        reward += STALEMATE_PENALTY;
    }



    //------------------------------------------------
    // Clamp reward
    //------------------------------------------------

    reward =
        std::clamp(
            reward,
            MIN_REWARD,
            MAX_REWARD);



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