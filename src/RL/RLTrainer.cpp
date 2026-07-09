#include "RLTrainer.h"

#include <iostream>
#include <filesystem>


//====================================================
// CONSTRUCTOR
//====================================================

RLTrainer::RLTrainer(
    std::shared_ptr<DecisionDL> network)
:
decisionDL(network)
{
}




//====================================================
// INITIALIZE
//====================================================

void RLTrainer::initialize()
{

    if(!decisionDL)
        return;


    optimizer =
        std::make_unique<torch::optim::Adam>(
            decisionDL->parameters(),
            torch::optim::AdamOptions(
                learningRate));


    initialized = true;


    std::cout
        << "[RLTrainer] Initialized"
        << std::endl;

}




//====================================================
// REMEMBER
//====================================================

void RLTrainer::remember(
    const torch::Tensor& stateAction)
{

    RLExperience experience;


    experience.stateAction =
        stateAction.clone();



    episode.push_back(
        experience);



    std::cout
        << "[RLTrainer] Stored action. "
        << "Episode size: "
        << episode.size()
        << std::endl;

}





//====================================================
// TRAIN EPISODE
//
// Supervised reinforcement update.
//
// Each action receives the final
// episode reward.
//
//====================================================

void RLTrainer::trainEpisode(
    float reward)
{

    if(!initialized)
        return;



    if(episode.empty())
    {
        std::cout
            << "[RLTrainer] Empty episode"
            << std::endl;

        return;
    }



    decisionDL->train();



    float totalLoss = 0.0f;



    for(const RLExperience& experience :
        episode)
    {


        //------------------------------------------------
        // Network prediction
        //------------------------------------------------

        torch::Tensor prediction =
            decisionDL->forward(
                experience.stateAction);



        //------------------------------------------------
        // Target reward
        //------------------------------------------------

        torch::Tensor target =
            torch::tensor(
                {
                    reward
                },
                torch::kFloat32);



        //------------------------------------------------
        // Loss
        //------------------------------------------------

        torch::Tensor loss =
            torch::mse_loss(
                prediction.squeeze(),
                target.squeeze());



        optimizer->zero_grad();


        loss.backward();


        optimizer->step();



        totalLoss +=
            loss.item<float>();

    }



    std::cout
        << "[RLTrainer] Episode trained"
        << " Reward: "
        << reward
        << " Loss: "
        << totalLoss
        << std::endl;



    clearEpisode();

}





//====================================================
// CLEAR EPISODE
//====================================================

void RLTrainer::clearEpisode()
{

    episode.clear();

}





//====================================================
// SAVE MODEL
//====================================================

bool RLTrainer::saveModel(
    const std::string& filename)
{

    if(!decisionDL)
        return false;

    std::cout
        << "Current path: "
        << std::filesystem::current_path()
        << std::endl;

    std::cout
        << "Saving to: "
        << filename
        << std::endl;

    try
    {

        torch::save(
            decisionDL,
            filename);

    }
    catch(const std::exception& e)
    {

        std::cout
            << "[RLTrainer] Save exception: "
            << e.what()
            << std::endl;

        return false;

    }

    return true;

}





//====================================================
// LOAD MODEL
//====================================================

bool RLTrainer::loadModel(
    const std::string& filename)
{

    if(!decisionDL)
        return false;



    try
    {

        torch::load(
            decisionDL,
            filename);

    }
    catch(...)
    {

        return false;

    }



    return true;

}