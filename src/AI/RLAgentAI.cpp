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
        << "Creating RLAgentAI\n";


    //------------------------------------------------
    // Create RL system
    //------------------------------------------------

    rlSystem =
        std::make_unique<RLSystem>();


    //------------------------------------------------
    // Initialize RL system
    //------------------------------------------------

    rlSystem->initialize();


    std::cout
        << "RLSystem initialized\n";
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

    std::cout << "[RLAgentAI] decide called\n";

    if(!rlSystem)
        return false;


    return rlSystem->decide(
        state,
        move
    );
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