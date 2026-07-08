#include "RLSystem.h"

#include <iostream>
#include <vector>


//====================================================
// CONSTRUCTOR
//====================================================

RLSystem::RLSystem()
{
    std::cout
        << "[RLSystem] Constructor"
        << std::endl;
}



//====================================================
// INITIALIZE
//====================================================

void RLSystem::initialize()
{

    std::cout
        << "[RLSystem] initialize()"
        << std::endl;


    if(initialized)
    {
        std::cout
            << "[RLSystem] Already initialized"
            << std::endl;

        return;
    }



    //------------------------------------------------
    // Create shared network
    //------------------------------------------------

    std::cout
        << "[RLSystem] Creating DecisionDL"
        << std::endl;


    decisionDL =
        std::make_shared<DecisionDL>();


    std::cout
        << "[RLSystem] DecisionDL created"
        << std::endl;



    //------------------------------------------------
    // Initialize network
    //------------------------------------------------

    std::cout
        << "[RLSystem] Initializing DecisionDL"
        << std::endl;


    decisionDL->initialize(
        DecisionDL::MAX_CHILDREN,
        64,
        DecisionDL::MAX_CHILDREN
    );


    std::cout
        << "[RLSystem] DecisionDL initialized"
        << std::endl;



    //------------------------------------------------
    // Create trainer
    //------------------------------------------------

    std::cout
        << "[RLSystem] Creating RLTrainer"
        << std::endl;


    trainer =
        std::make_unique<RLTrainer>(
            decisionDL
        );


    std::cout
        << "[RLSystem] RLTrainer created"
        << std::endl;



    //------------------------------------------------
    // Initialize trainer
    //------------------------------------------------

    std::cout
        << "[RLSystem] Initializing RLTrainer"
        << std::endl;


    trainer->initialize();


    std::cout
        << "[RLSystem] RLTrainer initialized"
        << std::endl;



    //------------------------------------------------
    // Reward system
    //------------------------------------------------

    std::cout
        << "[RLSystem] Reset reward"
        << std::endl;


    rewardSystem.reset();


    std::cout
        << "[RLSystem] Reward initialized"
        << std::endl;



    initialized = true;


    std::cout
        << "[RLSystem] Initialization complete"
        << std::endl;

}



//====================================================
// DECIDE
//====================================================

bool RLSystem::decide(
    const GameState& state,
    Move& move)
{

    std::cout
        << "[RLSystem] decide()"
        << std::endl;


    if(!initialized)
    {
        std::cout
            << "[RLSystem] ERROR: not initialized"
            << std::endl;

        return false;
    }



    //------------------------------------------------
    // Build tree
    //------------------------------------------------

    std::cout
        << "[RLSystem] Building tree"
        << std::endl;


    tree.build(
        state,
        searchDepth
    );


    std::cout
        << "[RLSystem] Tree built"
        << std::endl;



    const DecisionNode& root =
        tree.getRoot();


    std::cout
        << "[RLSystem] Children: "
        << root.children.size()
        << std::endl;



    if(root.children.empty())
    {
        std::cout
            << "[RLSystem] No legal moves"
            << std::endl;

        return false;
    }



    //------------------------------------------------
    // Random candidates
    //------------------------------------------------

    std::cout
        << "[RLSystem] Selecting candidates"
        << std::endl;


    std::vector<DecisionNode> candidates =
        decisionDL->selectChildren(
            root.children
        );


    std::cout
        << "[RLSystem] Selected "
        << candidates.size()
        << " candidates"
        << std::endl;



    if(candidates.empty())
    {
        std::cout
            << "[RLSystem] ERROR: empty candidates"
            << std::endl;

        return false;
    }



    //------------------------------------------------
    // Encode
    //------------------------------------------------

    std::cout
        << "[RLSystem] Encoding"
        << std::endl;


    torch::Tensor input =
        decisionDL->encodeChildren(
            candidates
        );


    std::cout
        << "[RLSystem] Input shape: "
        << input.sizes()
        << std::endl;



    //------------------------------------------------
    // Forward
    //------------------------------------------------

    std::cout
        << "[RLSystem] Forward"
        << std::endl;


    torch::Tensor qValues =
        decisionDL->forward(
            input
        );


    std::cout
        << "[RLSystem] Output shape: "
        << qValues.sizes()
        << std::endl;



    //------------------------------------------------
    // Best action
    //------------------------------------------------

    int64_t action =
        qValues.argmax(1)
               .item<int64_t>();


    std::cout
        << "[RLSystem] Best action: "
        << action
        << std::endl;



    if(action < 0 ||
       action >= static_cast<int64_t>(candidates.size()))
    {
        std::cout
            << "[RLSystem] Invalid action -> using 0"
            << std::endl;

        action = 0;
    }



    move =
        candidates[action].move;


    std::cout
        << "[RLSystem] Move selected"
        << std::endl;


    return true;

}