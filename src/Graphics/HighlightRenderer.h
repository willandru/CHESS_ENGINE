#pragma once

#include <cstdint>

class Shader;

class HighlightRenderer
{
public:

    static void render(
        Shader& shader,
        uint8_t square,
        float r,
        float g,
        float b,
        float alpha = 0.45f
    );

    static void renderDebug(Shader& shader);
};