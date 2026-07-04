#pragma once

class Shader;

struct BoardLayout
{
    float x;
    float y;

    float boardSize;
    float squareSize;
};

class ChessBoardRenderer
{
public:

    static BoardLayout getLayout();

    static void render(Shader& shader);
};