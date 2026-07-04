#pragma once

#include "Texture.h"

class Shader;

enum class ChessPiece
{
    None = 0,

    WhitePawn,
    WhiteKnight,
    WhiteBishop,
    WhiteRook,
    WhiteQueen,
    WhiteKing,

    BlackPawn,
    BlackKnight,
    BlackBishop,
    BlackRook,
    BlackQueen,
    BlackKing
};

class ChessPieceRenderer
{
public:

    static bool init();
    static void shutdown();

    static void render(
        Shader& shader,
        ChessPiece piece,
        int row,
        int col
    );

private:

    static Texture textures[12];
};