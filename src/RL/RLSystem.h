#pragma once


#include <torch/torch.h>

#include <memory>
#include <vector>
#include <string>
#include <cstdint>


#include "GameState.h"
#include "Move.h"

#include "DecisionTreeEngine.h"
#include "DecisionNode.h"

#include "DecisionDL.h"
#include "RLTrainer.h"
#include "RewardSystem.h"
#include "FeatureEngineering.h"



//====================================================
// RL SYSTEM
//
// Controls reinforcement learning process:
//
// - Generates candidate moves
// - Uses DecisionDL evaluation
// - Stores selected actions
// - Sends episode reward to trainer
//
//====================================================

class RLSystem
{

public:


    //------------------------------------------------
    // Constructor
    //------------------------------------------------

    RLSystem();



    //------------------------------------------------
    // Initialize RL system
    //------------------------------------------------

    void initialize();



    //------------------------------------------------
    // Start new game episode
    //------------------------------------------------

    void newEpisode();



    //------------------------------------------------
    // Finish game episode
    //
    // victory:
    //      true  -> win
    //      false -> loss
    //
    //------------------------------------------------

    void finishEpisode(
        bool victory);



    //------------------------------------------------
    // Decide next move
    //
    // Generates candidates,
    // evaluates them,
    // selects one.
    //
    //------------------------------------------------

    bool decide(
        const GameState& state,
        Move& move);



    //------------------------------------------------
    // Observe executed move
    //
    // Stores selected action
    // into current episode.
    //
    //------------------------------------------------

    void observe(
        const GameState& state);



    //------------------------------------------------
    // Training control
    //------------------------------------------------

    void setTrainingEnabled(
        bool enabled);



    bool isTrainingEnabled() const;



    //------------------------------------------------
    // Model persistence
    //------------------------------------------------

    bool saveModel(
        const std::string& filename);



    bool loadModel(
        const std::string& filename);




private:


    //------------------------------------------------
    // Encode candidate moves
    //
    // DecisionNode[]
    //
    // -> Tensor [N x inputSize]
    //
    //------------------------------------------------

    torch::Tensor encodeCandidates(
        const GameState& state);




    //------------------------------------------------
    // Check terminal node
    //------------------------------------------------

    bool isTerminal(
        const DecisionNode& node) const;




private:


    //------------------------------------------------
    // Decision tree
    //------------------------------------------------

    DecisionTreeEngine tree;




    //------------------------------------------------
    // Neural network
    //------------------------------------------------

    std::shared_ptr<DecisionDL> decisionDL;




    //------------------------------------------------
    // Trainer
    //------------------------------------------------

    std::unique_ptr<RLTrainer> trainer;




    //------------------------------------------------
    // Reward calculation
    //------------------------------------------------

    RewardSystem rewardSystem;




    //------------------------------------------------
    // Current possible moves
    //------------------------------------------------

    std::vector<DecisionNode> currentCandidates;




    //------------------------------------------------
    // Episode memory
    //
    // Stored by RLTrainer internally.
    //
    //------------------------------------------------




    //------------------------------------------------
    // Previous selected action
    //
    // Created in decide()
    // consumed in observe()
    //
    //------------------------------------------------

    torch::Tensor previousStateAction;



    DecisionNode previousNode;



    bool hasPreviousAction = false;




    //------------------------------------------------
    // Episode information
    //------------------------------------------------

    uint32_t turn = 0;




    //------------------------------------------------
    // Tree search depth
    //------------------------------------------------

    uint32_t searchDepth = 1;




    //------------------------------------------------
    // System state
    //------------------------------------------------

    bool trainingEnabled = true;



    bool initialized = false;

};