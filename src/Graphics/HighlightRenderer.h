#pragma once

class Shader;

class HighlightRenderer
{
public:

    // Resalta una casilla cualquiera
    static void render(
        Shader& shader,
        int row,
        int col,
        float r,
        float g,
        float b,
        float alpha = 0.45f
    );

    // Debug
    static void renderDebug(Shader& shader);
};