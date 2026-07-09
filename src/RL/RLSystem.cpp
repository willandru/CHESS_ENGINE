#include "RLSystem.h"

#include <iostream>


//====================================================
// CONSTRUCTOR
//====================================================

RLSystem::RLSystem()
{
}



//====================================================
// INITIALIZE
//====================================================

void RLSystem::initialize()
{

    if(initialized)
        return;



    //------------------------------------------------
    // Create neural network
    //------------------------------------------------

    decisionDL =
        std::make_shared<DecisionDL>();



    //------------------------------------------------
    // Initialize network
    //------------------------------------------------

    decisionDL->initialize(
        FeatureEngineering::inputSize(),
        128,
        64);



    //------------------------------------------------
    // Create trainer
    //------------------------------------------------

    trainer =
        std::make_unique<RLTrainer>(
            decisionDL);



    //------------------------------------------------
    // Initialize optimizer
    //------------------------------------------------

    trainer->initialize();



    //------------------------------------------------
    // Reset episode
    //------------------------------------------------

    newEpisode();



    initialized = true;
}



//====================================================
// NEW EPISODE
//====================================================

void RLSystem::newEpisode()
{

    turn = 0;

    hasPreviousTransition = false;

    previousStateAction =
        torch::Tensor();



    previousNode =
        DecisionNode{};



    rewardSystem.reset();



    if(trainer)
    {
        trainer->resetExploration();
    }
}



//====================================================
// FINISH EPISODE
//====================================================

void RLSystem::finishEpisode(
    const GameState& state)
{

    hasPreviousTransition = false;


    currentCandidates.clear();


    rewardSystem.reset();
}



//====================================================
// ENCODE CANDIDATES
//
// Converts:
//
// DecisionNode[]
//
// into:
//
// Tensor [N x inputSize]
//
//====================================================

torch::Tensor RLSystem::encodeCandidates(
    const GameState& state)
{

    if(currentCandidates.empty())
    {
        return torch::empty(
            {0, FeatureEngineering::inputSize()});
    }



    std::vector<torch::Tensor> tensors;


    tensors.reserve(
        currentCandidates.size());



    for(const DecisionNode& node :
        currentCandidates)
    {

        std::vector<float> features =
            FeatureEngineering::encode(
                state,
                node);



        tensors.push_back(
            torch::tensor(
                features));
    }



    return torch::stack(
        tensors);
}



//====================================================
// DECIDE MOVE
//
// Generates candidates,
// selects action,
// stores previous transition.
//
//====================================================

bool RLSystem::decide(
    const GameState& state,
    Move& move)
{

    if(!initialized)
        return false;



    //------------------------------------------------
    // Generate decision tree
    //------------------------------------------------

    tree.build(
        state,
        searchDepth);



    //------------------------------------------------
    // Obtain candidate nodes
    //------------------------------------------------

    const DecisionNode& root =
        tree.getRoot();



    currentCandidates =
        root.children;



    //------------------------------------------------
    // No possible moves
    //------------------------------------------------

    if(currentCandidates.empty())
    {
        return false;
    }



    //------------------------------------------------
    // Encode candidates
    //------------------------------------------------

    torch::Tensor candidateTensor =
        encodeCandidates(
            state);



    //------------------------------------------------
    // Select action using RL policy
    //------------------------------------------------

    uint32_t selected =
        trainer->selectAction(
            candidateTensor);



    if(selected >= currentCandidates.size())
    {
        selected = 0;
    }



    //------------------------------------------------
    // Store transition information
    //------------------------------------------------

    previousStateAction =
        candidateTensor[selected]
        .unsqueeze(0);



    previousNode =
        currentCandidates[selected];



    hasPreviousTransition = true;



    //------------------------------------------------
    // Return chosen move
    //------------------------------------------------

    move =
        currentCandidates[selected]
        .move;



    return true;
}

//====================================================
// OBSERVE ENVIRONMENT
//
// Called after the game engine executes
// the selected move.
//
// Creates:
//
// (state, action, reward, nextState)
//
// and sends it to RLTrainer.
//
//====================================================

void RLSystem::observe(
    const GameState& state)
{

    std::cout 
    << "[RL] OBSERVE CALLED"
    << std::endl;

    if(!hasPreviousTransition)
        return;



    //------------------------------------------------
    // Generate next state candidates
    //------------------------------------------------

    tree.build(
        state,
        searchDepth);



    const DecisionNode& root =
        tree.getRoot();



    std::vector<DecisionNode> nextCandidates =
        root.children;



    //------------------------------------------------
    // Encode next actions
    //------------------------------------------------

    torch::Tensor nextStateActions;



    if(nextCandidates.empty())
    {

        nextStateActions =
            torch::empty(
                {
                    0,
                    FeatureEngineering::inputSize()
                });
    }
    else
    {

        std::vector<torch::Tensor> tensors;


        tensors.reserve(
            nextCandidates.size());



        for(const DecisionNode& node :
            nextCandidates)
        {

            std::vector<float> features =
                FeatureEngineering::encode(
                    state,
                    node);



            tensors.push_back(
                torch::tensor(
                    features));
        }



        nextStateActions =
            torch::stack(
                tensors);
    }



    //------------------------------------------------
    // Calculate reward
    //------------------------------------------------

    float reward =
        rewardSystem.calculateReward(
            previousNode,
            turn);



    //------------------------------------------------
    // Create transition
    //------------------------------------------------

    RLTransition transition;


    transition.currentStateAction =
        previousStateAction.clone();



    transition.nextStateActions =
        nextStateActions.clone();



    transition.reward =
        reward;



    transition.done =
        isTerminal(
            previousNode);



            std::cout
    << "[RL] Reward generated: "
    << reward
    << std::endl;

    //------------------------------------------------
    // Store experience
    //------------------------------------------------

    trainer->remember(
        transition);



    //------------------------------------------------
    // Train network
    //------------------------------------------------

    if(trainingEnabled)
    {
        trainer->trainStep();
    }



    //------------------------------------------------
    // Prepare next turn
    //------------------------------------------------

    hasPreviousTransition = false;


    ++turn;
}



//====================================================
// TERMINAL CHECK
//====================================================

bool RLSystem::isTerminal(
    const DecisionNode& node) const
{

    return
        node.checkmate ||
        node.stalemate ||
        node.terminal;
}



//====================================================
// TRAINING CONTROL
//====================================================

void RLSystem::setTrainingEnabled(
    bool enabled)
{
    trainingEnabled = enabled;
}



//====================================================
// IS TRAINING ENABLED
//====================================================

bool RLSystem::isTrainingEnabled() const
{
    return trainingEnabled;
}



//====================================================
// SET EPSILON
//====================================================

void RLSystem::setEpsilon(
    float value)
{

    if(!trainer)
        return;


    //
    // Direct access to epsilon is intentionally
    // controlled by RLTrainer.
    //
    // This is a temporary testing interface.
    //

    trainer->resetExploration();
}



//====================================================
// GET EPSILON
//====================================================

float RLSystem::getEpsilon() const
{

    if(!trainer)
        return 0.0f;


    return trainer->getExplorationRate();
}



//====================================================
// SAVE MODEL
//====================================================

bool RLSystem::saveModel(
    const std::string& filename)
{

    if(!decisionDL)
        return false;


    try
    {

        trainer->saveModel(
            filename);

    }
    catch(...)
    {
        return false;
    }


    return true;
}



//====================================================
// LOAD MODEL
//====================================================

bool RLSystem::loadModel(
    const std::string& filename)
{

    if(!decisionDL)
        return false;


    try
    {

        trainer->loadModel(
            filename);

    }
    catch(...)
    {
        return false;
    }


    return true;
}