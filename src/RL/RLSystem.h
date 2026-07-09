#pragma once

#include <torch/torch.h>

#include <memory>
#include <string>
#include <vector>
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
// Reinforcement Learning System
//
// Coordinates:
//
// - Decision tree generation
// - Candidate action encoding
// - Neural network evaluation
// - Action selection policy
// - Reward calculation
// - Experience storage
// - Training
//
//====================================================

class RLSystem
{

public:


    //================================================
    // Constructor
    //================================================

    RLSystem();



    //================================================
    // Initialize complete RL system
    //================================================

    void initialize();



    //================================================
    // Episode control
    //================================================

    void newEpisode();



    void finishEpisode(
        const GameState& state);



    //================================================
    // Decide action
    //
    // Generates candidate moves,
    // selects one using RL policy,
    // stores transition information.
    //
    //================================================

    bool decide(
        const GameState& state,
        Move& move);



    //================================================
    // Observe environment
    //
    // Called after external engine
    // executes the selected move.
    //
    // Creates transition and trains.
    //
    //================================================

    void observe(
        const GameState& state);



    //================================================
    // Training control
    //================================================

    void setTrainingEnabled(
        bool enabled);



    bool isTrainingEnabled() const;



    //================================================
    // Exploration
    //================================================

    void setEpsilon(
        float value);



    float getEpsilon() const;



    //================================================
    // Model persistence
    //================================================

    bool saveModel(
        const std::string& filename);



    bool loadModel(
        const std::string& filename);



private:


    //================================================
    // Generate candidate tensor
    //
    // Converts DecisionNodes:
    //
    // [N nodes]
    //
    // into:
    //
    // [N x inputSize]
    //
    //================================================

    torch::Tensor encodeCandidates(
        const GameState& state);



    //================================================
    // Create RL transition
    //================================================

    void createTransition(
        const GameState& state);



    //================================================
    // Check terminal state
    //================================================

    bool isTerminal(
        const DecisionNode& node) const;



private:


    //================================================
    // Decision tree generator
    //================================================

    DecisionTreeEngine tree;



    //================================================
    // Deep Q Network
    //================================================

    std::shared_ptr<DecisionDL> decisionDL;



    //================================================
    // RL Trainer
    //
    // Contains:
    //
    // - Replay memory
    // - Bellman update
    // - Optimizer
    // - Epsilon greedy
    //
    //================================================

    std::unique_ptr<RLTrainer> trainer;



    //================================================
    // Reward system
    //================================================

    RewardSystem rewardSystem;



    //================================================
    // Current candidate nodes
    //
    // Index correspondence:
    //
    // candidates[i]
    //
    // tensor[i]
    //
    // action i
    //
    //================================================

    std::vector<DecisionNode> currentCandidates;



    //================================================
    // Previous transition data
    //
    // Stored after decide()
    //
    // Consumed by observe()
    //
    //================================================

    torch::Tensor previousStateAction;



    DecisionNode previousNode;



    bool hasPreviousTransition = false;



    //================================================
    // Episode data
    //================================================

    uint32_t turn = 0;



    //================================================
    // Tree search configuration
    //================================================

    uint32_t searchDepth = 1;



    //================================================
    // Training state
    //================================================

    bool trainingEnabled = true;



    bool initialized = false;

};