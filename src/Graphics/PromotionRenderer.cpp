#include "PromotionRenderer.h"

#include "Renderer.h"
#include "Shader.h"
#include "BoardView.h"

#include <iostream>

Texture PromotionRenderer::textures[8];

//====================================================
// INIT
//====================================================
bool PromotionRenderer::init()
{
    bool ok = true;

    ok &= textures[0].loadFromFile("Assets/dama_blanca.png");
    ok &= textures[1].loadFromFile("Assets/torre_blanca.png");
    ok &= textures[2].loadFromFile("Assets/alfil_blanco.png");
    ok &= textures[3].loadFromFile("Assets/caballo_blanco.png");

    ok &= textures[4].loadFromFile("Assets/dama_negra.png");
    ok &= textures[5].loadFromFile("Assets/torre_negra.png");
    ok &= textures[6].loadFromFile("Assets/alfil_negra.png");
    ok &= textures[7].loadFromFile("Assets/caballo_negro.png");

    if (!ok)
        std::cerr << "[PromotionRenderer] ERROR loading textures\n";

    return ok;
}

//====================================================
// SHUTDOWN
//====================================================
void PromotionRenderer::shutdown()
{
    for (int i = 0; i < 8; ++i)
        textures[i].destroy();
}

//====================================================
// RENDER
//====================================================
void PromotionRenderer::render(
    Shader& shader,
    bool whiteSide,
    const BoardView& view)
{
    float baseX = view.x + view.size + 20.0f;
    float baseY = view.y + view.size * 0.5f;

    float size = view.squareSize * optionSizeScale;
    float spacing = size + view.squareSize * spacingScale;

    std::cout << "[PromotionRenderer] whiteSide = " << whiteSide << "\n";

    for (int i = 0; i < 4; ++i)
    {
        float x = baseX;
        float y = baseY + i * spacing - 1.5f * spacing;

        int texIndex;

        if (whiteSide)
            texIndex = i;       // 0..3
        else
            texIndex = i + 4;   // 4..7

        //================================================
        // HARD SAFETY CHECK (CRITICAL)
        //================================================
        if (texIndex < 0 || texIndex >= 8)
        {
            std::cerr << "[PromotionRenderer] INVALID texIndex: " << texIndex << "\n";
            continue;
        }

        // DEBUG: detectar colapso de textura
        if (texIndex == 1)
        {
            std::cout << "[PromotionRenderer] RENDERING ROOK SLOT\n";
        }

        Renderer::drawTextureRect(
            x,
            y,
            size,
            size,
            textures[texIndex],
            shader
        );
    }
}

//====================================================
// PICKING
//====================================================
uint8_t PromotionRenderer::pickOption(
    float mouseX,
    float mouseY,
    const BoardView& view)
{
    float baseX = view.x + view.size + 20.0f;
    float baseY = view.y + view.size * 0.5f;

    float size = view.squareSize * optionSizeScale;
    float spacing = size + view.squareSize * spacingScale;

    for (int i = 0; i < 4; ++i)
    {
        float x = baseX;
        float y = baseY + i * spacing - 1.5f * spacing;

        bool inside =
            mouseX >= x &&
            mouseX <= x + size &&
            mouseY >= y &&
            mouseY <= y + size;

        if (inside)
            return static_cast<uint8_t>(i);
    }

    return 255;
}