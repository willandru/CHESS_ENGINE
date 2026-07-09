#include "RLAgentAI.h"

#include "RLSystem.h"

#include <iostream>


//====================================================
// DEFAULT CONSTRUCTOR
//====================================================

RLAgentAI::RLAgentAI()
{

    std::cout
        << "Creating RLAgentAI"
        << std::endl;


    rlSystem =
        std::make_unique<RLSystem>();


    rlSystem->initialize();

}



//====================================================
// MODEL CONSTRUCTOR
//====================================================

RLAgentAI::RLAgentAI(
    const char* path)
{

    std::cout
        << "Creating RLAgentAI"
        << std::endl;



    modelPath = path;



    rlSystem =
        std::make_unique<RLSystem>();


    //------------------------------------------------
    // Initialize neural system
    //------------------------------------------------

    rlSystem->initialize();



    std::cout
        << "[RLAgentAI] Model path: "
        << modelPath
        << std::endl;



    //------------------------------------------------
    // Load existing model
    //------------------------------------------------

    if(rlSystem->loadModel(modelPath))
    {

        std::cout
            << "[RLAgentAI] Model loaded"
            << std::endl;

    }

    else
    {

        std::cout
            << "[RLAgentAI] No model found"
            << std::endl;


        std::cout
            << "[RLAgentAI] Creating new model"
            << std::endl;



        //------------------------------------------------
        // Save initial random weights
        //------------------------------------------------

        if(rlSystem->saveModel(modelPath))
        {

            std::cout
                << "[RLAgentAI] New model created"
                << std::endl;

        }

        else
        {

            std::cout
                << "[RLAgentAI] Failed creating model"
                << std::endl;

        }

    }

}



//====================================================
// AGENT
//====================================================

bool RLAgentAI::isHuman() const
{
    return false;
}



//====================================================
// DECISION
//====================================================

bool RLAgentAI::decide(
    const GameState& state,
    Move& move)
{

    std::cout
        << "[RLAgentAI] decide called"
        << std::endl;



    if(!rlSystem)
        return false;



    return rlSystem->decide(
        state,
        move
    );

}



//====================================================
// OBSERVE
//====================================================

void RLAgentAI::observe(
    const GameState& state)
{

    if(!rlSystem)
        return;



    rlSystem->observe(
        state
    );

}



//====================================================
// FINISH GAME
//====================================================

void RLAgentAI::finishGame(
    bool win)
{

    if(!rlSystem)
        return;



    //------------------------------------------------
    // Finish episode + train
    //------------------------------------------------

    rlSystem->finishEpisode(
        win
    );



    //------------------------------------------------
    // Save updated weights
    //------------------------------------------------

    if(!modelPath.empty())
    {

        if(rlSystem->saveModel(modelPath))
        {

            std::cout
                << "[RLAgentAI] Model saved: "
                << modelPath
                << std::endl;

        }

        else
        {

            std::cout
                << "[RLAgentAI] Failed saving model"
                << std::endl;

        }

    }

}



//====================================================
// MODEL PATH
//====================================================

void RLAgentAI::setModelPath(
    const std::string& path)
{

    modelPath = path;

}



const std::string& RLAgentAI::getModelPath() const
{
    return modelPath;
}