#pragma once

#include <torch/torch.h>

#include <memory>
#include <vector>
#include <string>


#include "DecisionDL.h"



//====================================================
// EPISODE EXPERIENCE
//
// One selected action during a game.
//
// The final reward is applied when
// the game finishes.
//
//====================================================

struct RLExperience
{

    torch::Tensor stateAction;

};





//====================================================
// RL TRAINER
//
// Responsible for:
//
// - Storing episode actions
// - Training after episode result
// - Updating DecisionDL
// - Saving/loading model
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
    // Store one action
    //
    // Called every move.
    //
    //------------------------------------------------

    void remember(
        const torch::Tensor& stateAction);




    //------------------------------------------------
    // Train after complete game
    //
    // reward:
    //
    // positive -> victory
    // negative -> defeat
    //
    //------------------------------------------------

    void trainEpisode(
        float reward);




    //------------------------------------------------
    // Clear episode memory
    //------------------------------------------------

    void clearEpisode();




    //------------------------------------------------
    // Persistence
    //------------------------------------------------

    bool saveModel(
        const std::string& filename);



    bool loadModel(
        const std::string& filename);



private:


    //------------------------------------------------
    // Neural network
    //------------------------------------------------

    std::shared_ptr<DecisionDL> decisionDL;




    //------------------------------------------------
    // Optimizer
    //------------------------------------------------

    std::unique_ptr<
        torch::optim::Adam> optimizer;




    //------------------------------------------------
    // Current episode
    //------------------------------------------------

    std::vector<RLExperience> episode;




    //------------------------------------------------
    // Hyperparameters
    //------------------------------------------------

    float learningRate = 0.001f;



    //------------------------------------------------
    // State
    //------------------------------------------------

    bool initialized = false;

};