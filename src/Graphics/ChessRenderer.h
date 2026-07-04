#pragma once

class Shader;
class ChessGame;

class ChessRenderer
{
public:

    static void render(
        Shader& boardShader,
        Shader& pieceShader,
        const ChessGame& game);
};