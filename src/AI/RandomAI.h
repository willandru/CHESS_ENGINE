#pragma once

#include <cstdint>
#include "Move.h"

class GameState;

class RandomAI
{
public:
    RandomAI();

    void requestMove(const GameState& state);

    bool hasMove() const;
    Move getMove() const;

    void clear(); // <- SOLO ESTO (no reset)

private:
    Move selectedMove;
    bool ready = false;
};