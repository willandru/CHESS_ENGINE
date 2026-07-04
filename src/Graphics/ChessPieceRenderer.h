#pragma once

#include <cstdint>

#include "Texture.h"
#include "GameState.h"

class Shader;

class ChessPieceRenderer
{
public:

    static bool init();
    static void shutdown();

    static void render(
        Shader& shader,
        Piece piece,
        uint8_t square
    );

private:

    static Texture textures[12];
};