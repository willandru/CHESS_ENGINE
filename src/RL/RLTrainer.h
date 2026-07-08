#pragma once

#include <torch/torch.h>

#include <memory>
#include <vector>
#include <cstdint>

#include "DecisionDL.h"

//====================================================
// Experience
//====================================================

struct RLTransition
{
    torch::Tensor state;

    int64_t action;

    float reward;

    torch::Tensor nextState;

    bool done;
};

//====================================================
// RL Trainer
//====================================================

class RLTrainer
{

public:

    explicit RLTrainer(
        std::shared_ptr<DecisionDL> network);

    void initialize();

    void remember(
        const RLTransition& transition);

    void trainStep();

    bool isInitialized() const;

    void saveModel(
        const std::string& file);

    void loadModel(
        const std::string& file);



private:

    torch::Tensor calculateTarget(
        const RLTransition& transition);



private:

    //------------------------------------------------
    // Shared network
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
    // Hyperparameters
    //------------------------------------------------

    float gamma = 0.99f;

    float learningRate = 0.001f;

    uint32_t batchSize = 64;

    uint32_t replayCapacity = 50000;



    bool initialized = false;

};