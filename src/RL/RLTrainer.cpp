#include "RLTrainer.h"

#include <algorithm>
#include <random>
#include <iterator>

#include <iostream>
//====================================================
// CONSTRUCTOR
//====================================================

RLTrainer::RLTrainer(
    std::shared_ptr<DecisionDL> network)
:
decisionDL(network),
rng(std::random_device{}())
{
}



//====================================================
// INITIALIZE
//====================================================

void RLTrainer::initialize()
{
    if (!decisionDL)
        return;


    optimizer =
        std::make_unique<torch::optim::Adam>(
            decisionDL->parameters(),
            torch::optim::AdamOptions(
                learningRate));


    initialized = true;
}



//====================================================
// STATUS
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

    RLTransition copy;


    //------------------------------------------------
    // Clone tensors
    //
    // Avoid references to temporary tensors
    //------------------------------------------------

    copy.currentStateAction =
        transition.currentStateAction.clone();


    copy.nextStateActions =
        transition.nextStateActions.clone();



    //------------------------------------------------
    // Copy scalar data
    //------------------------------------------------

    copy.reward =
        transition.reward;


    copy.done =
        transition.done;



    //------------------------------------------------
    // Store experience
    //------------------------------------------------

    replayBuffer.push_back(
        std::move(copy));

        std::cout 
        << "[RL] Experience stored. Replay size: "
        << replayBuffer.size()
        << " Reward: "
        << transition.reward
        << " Done: "
        << transition.done
        << std::endl;




    //------------------------------------------------
    // Maintain capacity
    //------------------------------------------------

    if(replayBuffer.size() > replayCapacity)
    {
        replayBuffer.erase(
            replayBuffer.begin());
    }
}



//====================================================
// CLEAR REPLAY MEMORY
//====================================================

void RLTrainer::clearReplayMemory()
{
    replayBuffer.clear();
}



//====================================================
// REPLAY SIZE
//====================================================

std::size_t RLTrainer::getReplaySize() const
{
    return replayBuffer.size();
}



//====================================================
// COMPUTE TARGET
//
// target:
//
// done:
//      reward
//
// else:
//      reward + gamma * max(Q(next))
//
//====================================================

torch::Tensor RLTrainer::computeTarget(
    const RLTransition& transition)
{

    torch::NoGradGuard guard;



    //------------------------------------------------
    // Terminal state
    //------------------------------------------------

    if(transition.done)
    {
        return torch::tensor(
            transition.reward,
            torch::kFloat32);
    }



    //------------------------------------------------
    // Evaluate next possible actions
    //------------------------------------------------

    torch::Tensor nextQ =
        decisionDL->forward(
            transition.nextStateActions);



    //------------------------------------------------
    // Best future action value
    //------------------------------------------------

    torch::Tensor maxNextQ =
        nextQ.max();



    //------------------------------------------------
    // Bellman equation
    //------------------------------------------------

    return
        torch::tensor(
            transition.reward,
            torch::kFloat32)
        +
        gamma * maxNextQ;
}



//====================================================
// SELECT ACTION
//
// ε-greedy policy:
//
// epsilon probability:
//      random exploration
//
// otherwise:
//      best predicted Q value
//
//====================================================

//====================================================
// SELECT ACTION
//
// Selects the best candidate according to DecisionDL.
//
// Input:
//      candidateStateActions [N x inputSize]
//
// Output:
//      index of selected candidate
//
//====================================================

uint32_t RLTrainer::selectAction(
    const torch::Tensor& candidateStateActions)
{
    if(candidateStateActions.size(0) == 0)
        return 0;


    return greedyAction(
        candidateStateActions);
}



//====================================================
// GREEDY ACTION
//
// Uses neural network prediction.
//
// The candidate with highest Q value
// is selected.
//
//====================================================

uint32_t RLTrainer::greedyAction(
    const torch::Tensor& candidateStateActions)
{
    torch::NoGradGuard guard;


    decisionDL->eval();


    torch::Tensor qValues =
        decisionDL->forward(
            candidateStateActions);



    std::cout
        << "[RL] Q values:\n"
        << qValues
        << std::endl;



    int64_t index =
        qValues.argmax()
        .item<int64_t>();



    std::cout
        << "[RL] Selected action index: "
        << index
        << std::endl;



    return static_cast<uint32_t>(
        index);
}



//====================================================
// RANDOM ACTION
//====================================================

uint32_t RLTrainer::randomAction(
    uint32_t actionCount)
{

    if(actionCount == 0)
        return 0;


    std::uniform_int_distribution<uint32_t>
        distribution(
            0,
            actionCount - 1);


    return distribution(rng);
}

//====================================================
// UPDATE EXPLORATION
//
// Decays epsilon after training.
//
// epsilon:
//
// high -> more exploration
//
// low -> more exploitation
//
//====================================================

//====================================================
// UPDATE EXPLORATION
//
// Disabled because action selection
// is deterministic.
//
//====================================================

void RLTrainer::updateExploration()
{
}



//====================================================
// RESET EXPLORATION
//
// Used when starting a new training session.
//
//====================================================

//====================================================
// RESET EXPLORATION
//
// Exploration disabled for deterministic policy.
//
//====================================================

void RLTrainer::resetExploration()
{
    epsilon = 0.0f;
}



//====================================================
// GET EXPLORATION RATE
//====================================================

float RLTrainer::getExplorationRate() const
{
    return epsilon;
}



//====================================================
// TRAIN STEP
//
// Performs one optimization step.
//
// Algorithm:
//
// 1. Sample experience batch
// 2. Compute Q(current)
// 3. Compute Bellman target
// 4. Calculate loss
// 5. Backpropagation
//
//====================================================

void RLTrainer::trainStep()
{

    if(!initialized)
        return;



    //------------------------------------------------
    // Wait until enough experiences exist
    //------------------------------------------------

    if(replayBuffer.size() < batchSize)
    {
        std::cout
            << "[RL] Waiting experiences: "
            << replayBuffer.size()
            << "/"
            << batchSize
            << std::endl;

        return;
    }



    //------------------------------------------------
    // Create random batch
    //------------------------------------------------

    std::vector<RLTransition> batch;


    std::sample(
        replayBuffer.begin(),
        replayBuffer.end(),
        std::back_inserter(batch),
        batchSize,
        rng);



    //------------------------------------------------
    // Training mode
    //------------------------------------------------

    decisionDL->train();



    //------------------------------------------------
    // Iterate experiences
    //------------------------------------------------

    for(const RLTransition& transition : batch)
    {


        //------------------------------------------------
        // Current Q(s,a)
        //------------------------------------------------

        torch::Tensor currentQ =
            decisionDL->forward(
                transition.currentStateAction);



        //------------------------------------------------
        // Bellman target
        //------------------------------------------------

        torch::Tensor target =
            computeTarget(
                transition);



        //------------------------------------------------
        // Mean Squared Error
        //------------------------------------------------

        torch::Tensor loss =
            torch::mse_loss(
                currentQ.squeeze(),
                target);

            std::cout
            << "[RL] Training step"
            << " Loss: "
            << loss.item<float>()
            << std::endl;



        //------------------------------------------------
        // Optimization
        //------------------------------------------------

        optimizer->zero_grad();


        loss.backward();


        optimizer->step();

    }



    //------------------------------------------------
    // Reduce exploration after learning step
    //------------------------------------------------

    updateExploration();
}



//====================================================
// SAVE MODEL
//====================================================

void RLTrainer::saveModel(
    const std::string& file)
{
    if(!decisionDL)
        return;


    torch::serialize::OutputArchive archive;


    decisionDL->save(
        archive);


    archive.save_to(
        file);
}



//====================================================
// LOAD MODEL
//====================================================

void RLTrainer::loadModel(
    const std::string& file)
{
    if(!decisionDL)
        return;


    torch::serialize::InputArchive archive;


    archive.load_from(
        file);


    decisionDL->load(
        archive);
}