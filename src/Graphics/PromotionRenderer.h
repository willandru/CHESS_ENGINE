#pragma once

#include <cstdint>

#include "Texture.h"
#include "ChessTypes.h"

class Shader;
struct BoardView;

class PromotionRenderer
{
public:

    static bool init();
    static void shutdown();

    //====================================================
    // Render UI
    //====================================================
    static void render(
        Shader& shader,
        bool whiteSide,
        const BoardView& view);

    //====================================================
    // Input picking
    //====================================================
    static uint8_t pickOption(
        float mouseX,
        float mouseY,
        const BoardView& view);

private:

    static Texture textures[8];

    static constexpr float optionSizeScale = 0.7f;
    static constexpr float spacingScale    = 0.15f;
};