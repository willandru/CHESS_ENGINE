#pragma once

#include <vector>

#include "Move.h"

class Renderer3D;
class Shader3D;
class Camera3D;
class ChessGame;

class HighlightRenderer3D
{
public:

    void render(
        Renderer3D& renderer,
        Shader3D& shader,
        Camera3D& camera,
        float aspectRatio,
        const ChessGame& game
    );

private:

    void renderSquare(
        Renderer3D& renderer,
        Shader3D& shader,
        Camera3D& camera,
        float aspectRatio,
        uint8_t square,
        float r,
        float g,
        float b
    );

    void renderMoves(
        Renderer3D& renderer,
        Shader3D& shader,
        Camera3D& camera,
        float aspectRatio,
        const std::vector<Move>& moves,
        float r,
        float g,
        float b
    );
};