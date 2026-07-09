#pragma once

#include <torch/torch.h>

#include <memory>
#include <vector>
#include <string>
#include <cstdint>
#include <random>

#include "DecisionDL.h"


//====================================================
// Reinforcement Learning Transition
//
// Represents one experience:
//
// (state + action, reward,
//  next candidate actions, done)
//
//====================================================

struct RLTransition
{
    //------------------------------------------------
    // Current (state, action)
    //
    // Shape:
    // [1 x inputSize]
    //------------------------------------------------

    torch::Tensor currentStateAction;


    //------------------------------------------------
    // Candidate actions of next state
    //
    // Shape:
    // [N x inputSize]
    //------------------------------------------------

    torch::Tensor nextStateActions;


    //------------------------------------------------
    // Immediate reward
    //------------------------------------------------

    float reward = 0.0f;


    //------------------------------------------------
    // Terminal state
    //------------------------------------------------

    bool done = false;
};



//====================================================
// Reinforcement Learning Trainer
//
// Responsibilities:
//
// - Experience replay
// - Bellman target calculation
// - Network optimization
// - Action selection policy
// - Exploration / exploitation control
// - Model persistence
//
//====================================================

class RLTrainer
{

public:


    //------------------------------------------------
    // Constructor
    //------------------------------------------------

    explicit RLTrainer(
        std::shared_ptr<DecisionDL> network);



    //------------------------------------------------
    // Initialize optimizer
    //------------------------------------------------

    void initialize();



    //------------------------------------------------
    // Store experience
    //------------------------------------------------

    void remember(
        const RLTransition& transition);



    //------------------------------------------------
    // Train one optimization step
    //------------------------------------------------

    void trainStep();



    //------------------------------------------------
    // Action Selection
    //
    // Uses ε-greedy policy:
    //
    // exploration:
    // random action
    //
    // exploitation:
    // highest Q value
    //
    //------------------------------------------------

    uint32_t selectAction(
        const torch::Tensor& candidateStateActions);



    //------------------------------------------------
    // Exploration control
    //------------------------------------------------

    void resetExploration();


    float getExplorationRate() const;



    //------------------------------------------------
    // Replay memory
    //------------------------------------------------

    void clearReplayMemory();


    std::size_t getReplaySize() const;



    //------------------------------------------------
    // Persistence
    //------------------------------------------------

    void saveModel(
        const std::string& file);


    void loadModel(
        const std::string& file);



    //------------------------------------------------
    // Status
    //------------------------------------------------

    bool isInitialized() const;



private:


    //------------------------------------------------
    // Bellman target
    //
    // target =
    // reward + gamma * max(Q(next))
    //
    //------------------------------------------------

    torch::Tensor computeTarget(
        const RLTransition& transition);



    //------------------------------------------------
    // Policy helpers
    //------------------------------------------------

    uint32_t greedyAction(
        const torch::Tensor& candidateStateActions);



    uint32_t randomAction(
        uint32_t actionCount);



    void updateExploration();



private:


    //------------------------------------------------
    // Neural network
    //------------------------------------------------

    std::shared_ptr<DecisionDL> decisionDL;



    //------------------------------------------------
    // Replay memory
    //------------------------------------------------

    std::vector<RLTransition> replayBuffer;



    //------------------------------------------------
    // Optimizer
    //------------------------------------------------

    std::unique_ptr<torch::optim::Adam> optimizer;



    //------------------------------------------------
    // Q-Learning Hyperparameters
    //------------------------------------------------

    float gamma = 0.99f;


    float learningRate = 0.001f;



    //------------------------------------------------
    // Training parameters
    //------------------------------------------------

    uint32_t batchSize = 4;


    uint32_t replayCapacity = 50000;



    //------------------------------------------------
    // ε-Greedy exploration parameters
    //------------------------------------------------

    // Initial exploration probability

    float epsilon = 0.0f;


    // Minimum exploration probability

    float epsilonMin = 0.05f;


    // Decay after training steps

    float epsilonDecay = 0.995f;



    //------------------------------------------------
    // Random generator
    //------------------------------------------------

    std::mt19937 rng;



    //------------------------------------------------
    // Initialization state
    //------------------------------------------------

    bool initialized = false;

};