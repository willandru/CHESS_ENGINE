#pragma once

#include "Agent.h"

#include <memory>


class RLSystem;



class RLAgentAI : public Agent
{

public:

    RLAgentAI();


    bool isHuman() const override;


    bool decide(
        const GameState& state,
        Move& move
    ) override;



private:

    std::unique_ptr<RLSystem> rlSystem;

};