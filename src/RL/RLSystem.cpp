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



    trainer->initialize();



    //------------------------------------------------
    // Start first episode
    //------------------------------------------------

    newEpisode();



    initialized = true;



    std::cout
        << "[RLSystem] Initialized"
        << std::endl;

}





//====================================================
// NEW EPISODE
//====================================================

void RLSystem::newEpisode()
{

    turn = 0;


    hasPreviousAction = false;



    previousStateAction =
        torch::Tensor();



    previousNode =
        DecisionNode();



    currentCandidates.clear();



    rewardSystem.reset();



    if(trainer)
    {
        trainer->clearEpisode();
    }



    std::cout
        << "[RLSystem] New episode"
        << std::endl;

}





//====================================================
// ENCODE CANDIDATES
//
// DecisionNode list:
//
// [N nodes]
//
// becomes:
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
        {
            0,
            static_cast<int64_t>(
                FeatureEngineering::inputSize())
        });

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
// Generates candidate moves,
// evaluates them with DecisionDL,
// stores selected action.
//
//====================================================

bool RLSystem::decide(
    const GameState& state,
    Move& move)
{

    if(!initialized)
        return false;



    //------------------------------------------------
    // Build decision tree
    //------------------------------------------------

    tree.build(
        state,
        searchDepth);



    //------------------------------------------------
    // Get candidates
    //------------------------------------------------

    const DecisionNode& root =
        tree.getRoot();



    currentCandidates =
        root.children;



    if(currentCandidates.empty())
    {

        std::cout
            << "[RLSystem] No candidates"
            << std::endl;


        return false;
    }





    //------------------------------------------------
    // Encode candidates
    //------------------------------------------------

    torch::Tensor candidates =
        encodeCandidates(
            state);





    //------------------------------------------------
    // Select best action
    //
    // DecisionDL output:
    //
    // Q values per candidate
    //
    //------------------------------------------------

    torch::Tensor values =
        decisionDL->evaluate(
            state,
            currentCandidates);



    int64_t index =
        values.argmax()
        .item<int64_t>();




    if(index < 0 ||
       index >= static_cast<int64_t>(
            currentCandidates.size()))
    {

        index = 0;

    }





    //------------------------------------------------
    // Store selected action
    //
    // Used by observe()
    //
    //------------------------------------------------

    previousStateAction =
        candidates[index]
        .unsqueeze(0);



    previousNode =
        currentCandidates[index];



    hasPreviousAction = true;





    //------------------------------------------------
    // Return move
    //------------------------------------------------

    move =
        currentCandidates[index]
        .move;



    std::cout
        << "[RLSystem] Selected action: "
        << index
        << std::endl;



    return true;

}






//====================================================
// OBSERVE
//
// Called after game engine executes
// the selected move.
//
// Stores action in RLTrainer.
//
//====================================================

void RLSystem::observe(
    const GameState& state)
{

    if(!hasPreviousAction)
        return;



    if(!trainer)
        return;




    //------------------------------------------------
    // Store experience
    //------------------------------------------------

    trainer->remember(
        previousStateAction);



    std::cout
        << "[RLSystem] Action stored"
        << std::endl;




    //------------------------------------------------
    // Clear temporary action
    //------------------------------------------------

    previousStateAction =
        torch::Tensor();



    previousNode =
        DecisionNode();



    hasPreviousAction = false;



    turn++;

}

//====================================================
// FINISH EPISODE
//
// Called when game ends.
//
// victory:
//      true  -> win
//      false -> loss
//
// Applies final reward and trains network.
//
//====================================================

void RLSystem::finishEpisode(
    bool victory)
{

    if(!trainer)
        return;



    //------------------------------------------------
    // Calculate final reward
    //------------------------------------------------

    float reward = 0.0f;



    if(victory)
    {
        reward = 100.0f;
    }
    else
    {
        reward = -100.0f;
    }



    //------------------------------------------------
    // Time penalty
    //------------------------------------------------

    reward -=
        static_cast<float>(turn);



    std::cout
        << "[RLSystem] Episode finished"
        << std::endl;


    std::cout
        << "[RLSystem] Turns: "
        << turn
        << std::endl;


    std::cout
        << "[RLSystem] Reward: "
        << reward
        << std::endl;




    //------------------------------------------------
    // Train network
    //------------------------------------------------

    if(trainingEnabled)
    {

        trainer->trainEpisode(
            reward);


        std::cout
            << "[RLSystem] Training complete"
            << std::endl;

    }




    //------------------------------------------------
    // Reset episode
    //------------------------------------------------

    newEpisode();

}







//====================================================
// TERMINAL CHECK
//
// Checks if node ends game.
//
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



    std::cout
        << "[RLSystem] Training "
        << (enabled ? "enabled" : "disabled")
        << std::endl;

}





bool RLSystem::isTrainingEnabled() const
{
    return trainingEnabled;
}








//====================================================
// SAVE MODEL
//====================================================

bool RLSystem::saveModel(
    const std::string& filename)
{

    if(!trainer)
        return false;



    bool result =
        trainer->saveModel(
            filename);



    if(result)
    {
        std::cout
            << "[RLSystem] Model saved: "
            << filename
            << std::endl;
    }
    else
    {
        std::cout
            << "[RLSystem] Save failed"
            << std::endl;
    }



    return result;

}







//====================================================
// LOAD MODEL
//====================================================

bool RLSystem::loadModel(
    const std::string& filename)
{

    if(!trainer)
        return false;



    bool result =
        trainer->loadModel(
            filename);



    if(result)
    {
        std::cout
            << "[RLSystem] Model loaded: "
            << filename
            << std::endl;
    }
    else
    {
        std::cout
            << "[RLSystem] Load failed"
            << std::endl;
    }



    return result;

}