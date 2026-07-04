#pragma once

#include <vector>
#include <cstdint>

#include "GameState.h"
#include "Move.h"

class CaptureAI
{
public:

    CaptureAI();
    void requestMove(const GameState& state);

    bool hasMove() const;
    Move getMove() const;

    void clear();

private:
    Move selectedMove;
    bool ready = false;
};