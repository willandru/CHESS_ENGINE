#pragma once

#include <cstdint>
#include <vector>

#include "Move.h"

class Shader;
struct BoardView;

class HighlightRenderer
{
public:

    static void render(
        Shader& shader,
        uint8_t square,
        float r,
        float g,
        float b,
        const BoardView& view
    );

    static void renderMoves(
        Shader& shader,
        const std::vector<Move>& moves,
        float r,
        float g,
        float b,
        const BoardView& view
    );
};