#include "RLTrainer.h"

#include <algorithm>
#include <random>

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
}



//====================================================
// INITIALIZED?
//====================================================

bool RLTrainer::isInitialized() const
{
    return initialized;
}



//====================================================
// REMEMBER
//====================================================

void RLTrainer::remember(
    const RLTransition& transition)
{

    replayBuffer.push_back(
        transition);

    if(replayBuffer.size() > replayCapacity)
    {
        replayBuffer.erase(
            replayBuffer.begin());
    }

}



//====================================================
// TARGET
//====================================================

torch::Tensor RLTrainer::calculateTarget(
    const RLTransition& transition)
{

    torch::NoGradGuard noGrad;

    if(transition.done)
    {
        return torch::tensor(
            transition.reward,
            torch::kFloat32);
    }

    torch::Tensor nextQ =
        decisionDL->forward(
            transition.nextState);

    torch::Tensor maxNext =
        std::get<0>(
            nextQ.max(1));

    return torch::tensor(
        transition.reward,
        torch::kFloat32)
        +
        gamma * maxNext;

}



//====================================================
// TRAIN
//====================================================

void RLTrainer::trainStep()
{

    if(!initialized)
        return;

    if(replayBuffer.size() < batchSize)
        return;

    std::vector<RLTransition> batch;

    std::sample(
        replayBuffer.begin(),
        replayBuffer.end(),
        std::back_inserter(batch),
        batchSize,
        std::mt19937{
            std::random_device{}()
        });

    for(const RLTransition& transition : batch)
    {

        torch::Tensor qValues =
            decisionDL->forward(
                transition.state);

        torch::Tensor action =
            torch::tensor(
                {{transition.action}},
                torch::kLong);

        torch::Tensor currentQ =
            qValues.gather(
                1,
                action);

        torch::Tensor target =
            calculateTarget(
                transition);

        torch::Tensor loss =
            torch::mse_loss(
                currentQ.squeeze(),
                target.squeeze());

        optimizer->zero_grad();

        loss.backward();

        optimizer->step();
    }

}



//====================================================
// SAVE
//====================================================

void RLTrainer::saveModel(
    const std::string& file)
{
    torch::save(
        decisionDL,
        file);
}



//====================================================
// LOAD
//====================================================

void RLTrainer::loadModel(
    const std::string& file)
{
    torch::load(
        decisionDL,
        file);
}