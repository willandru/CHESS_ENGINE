#pragma once

#include <cstdint>
#include "Texture.h"
#include "ChessTypes.h"

class Shader;
struct BoardView;

class ChessPieceRenderer
{
public:
    static bool init();
    static void shutdown();

    static void render(
        Shader& shader,
        Piece piece,
        uint8_t square,
        const BoardView& view
    );

private:
    static Texture textures[12];
};