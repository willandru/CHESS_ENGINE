#include "RLAgentAI.h"

#include "RLSystem.h"
#include "AgentRegistry.h"

#include <iostream>
#include <memory>


//====================================================
// CONSTRUCTOR
//====================================================

RLAgentAI::RLAgentAI()
{
    std::cout
        << "Creating RLAgentAI"
        << std::endl;


    rlSystem =
        std::make_unique<RLSystem>();


    rlSystem->initialize();


    std::cout
        << "RLSystem initialized"
        << std::endl;
}



//====================================================
// AGENT TYPE
//====================================================

bool RLAgentAI::isHuman() const
{
    return false;
}



//====================================================
// DECIDE MOVE
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
        move);
}



//====================================================
// OBSERVE RESULT
//
// Called after the engine executes
// the selected move.
//
//====================================================

void RLAgentAI::observe(
    const GameState& state)
{
    std::cout
        << "[RLAgentAI] observe called"
        << std::endl;


    if(!rlSystem)
        return;


    rlSystem->observe(state);
}



//====================================================
// FINISH GAME
//
// Called when game ends.
//
// victory:
//      true  -> RL won
//      false -> RL lost
//
//====================================================

void RLAgentAI::finishGame(
    bool victory)
{

    if(!rlSystem)
        return;


    rlSystem->finishEpisode(
        victory);
}



//====================================================
// SAVE MODEL
//====================================================

bool RLAgentAI::saveModel(
    const std::string& filename)
{

    if(!rlSystem)
        return false;


    return rlSystem->saveModel(
        filename);
}



//====================================================
// LOAD MODEL
//====================================================

bool RLAgentAI::loadModel(
    const std::string& filename)
{

    if(!rlSystem)
        return false;


    return rlSystem->loadModel(
        filename);
}



//====================================================
// REGISTRATION
//====================================================

namespace
{

const bool registered = []()
{

    AgentRegistry::registerAgent(
        "RLAgentAI",
        []() -> std::unique_ptr<Agent>
        {
            return std::make_unique<RLAgentAI>();
        }
    );


    return true;

}();

}